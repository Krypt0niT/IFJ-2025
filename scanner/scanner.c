#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "../utilities/trim.h"

typedef struct {
    TokenType type;
    const char *name; // stringová reprezentácia
} TokenInfo;

static const TokenInfo tokenInfos[] = {
    {TOKEN_CLASS, "class"},
    {TOKEN_IF, "if"},
    {TOKEN_ELSE, "else"},
    {TOKEN_IS, "is"},
    {TOKEN_NULL, "null"},
    {TOKEN_RETURN, "return"},
    {TOKEN_VAR, "var"},
    {TOKEN_WHILE, "while"},
    {TOKEN_IFJ, "Ifj"},
    {TOKEN_STATIC, "static"},
    {TOKEN_IMPORT, "import"},
    {TOKEN_FOR, "for"},
    {TOKEN_NUM, "Num"},
    {TOKEN_STRING, "String"},
    {TOKEN_NULL_LITERAL, "Null"},
};

typedef enum {
    STATE_NONE,
    STATE_TEXT,
    STATE_NUM,
    STATE_SYMBOL,
    STATE_STRING

} StateType;

TokenType *string_to_token_type(const char* str);
Token* get_empty_token(TokenType token_type);
Token* get_token(TokenType token_type, char *value);
int success_empty_token(TokenType token_type, Token **out_token);
int success_token(TokenType token_type, char *value, Token **out_token);

void dispose_token(Token *token) {
    free(token->value);
    free(token);
}

Token* get_empty_token(TokenType token_type){
    Token *token = malloc(sizeof(Token));
    token->type = token_type;
    token->value = NULL;
    return token;
}

Token* get_token(TokenType token_type, char *value){
    Token *token = malloc(sizeof(Token));
    token->type = token_type;
    int value_length = strlen(value);
    token->value = malloc(value_length * sizeof(char));
    strcpy(token->value, value);
    return token;
}

FILE *__input_file = NULL;
char *__word_buffer = NULL;

void scanner_init(FILE *input_file) {
    __input_file = input_file;
}

int get_next_token(Token **out_token) {
    if (__input_file == NULL) {
        return NULL;
    }

    int word_buffer_size = 10;
    __word_buffer = calloc(word_buffer_size, sizeof(char));

    int word_length = 0;
    StateType automat_state = STATE_NONE;
    int c;
    while ((c = getc(__input_file)) != EOF) {
        char new_character = c;

        if (word_length == 0 && new_character == '\n') return success_empty_token(TOKEN_LINE_END, out_token); 

        // ten new character asi inak zariadit
        if (automat_state == STATE_NONE && new_character != ' ') {
            if (isalpha(new_character) != 0) automat_state = STATE_TEXT;
            if (isdigit(new_character) != 0) automat_state = STATE_NUM;
            if (isdigit(new_character) == 0 && isalpha(new_character) == 0) automat_state = STATE_SYMBOL;
            if (new_character == '"') automat_state = STATE_STRING;
        }
        
        char *trimmed_buffer = trim(__word_buffer);

        if (automat_state == STATE_TEXT) {
            if (isdigit(new_character) == 0 && isalpha(new_character) == 0) {
                //ungetc(new_character, __input_file);
                // skontroluj ci nieje identifikator
                // 
                TokenType *reserved_word = string_to_token_type(trimmed_buffer);
                if (reserved_word != NULL) {
                    return success_empty_token(*reserved_word, out_token); 
                }

                return success_token(TOKEN_ID, trimmed_buffer, out_token); 
            }
        }

        if (automat_state == STATE_NUM) {
            if (isdigit(new_character) == 0 && isalpha(new_character) == 0) {
                ungetc(new_character, __input_file);
                //TODO: 
                
                return success_token(TOKEN_INT_LITERAL, trimmed_buffer, out_token); 
            }
        }

        if (automat_state == STATE_SYMBOL) {
            if (isdigit(new_character) != 0 || isalpha(new_character) != 0 || new_character == ' ') {
                //ungetc(new_character, __input_file);
                //TODO: opravit
                if (strcmp("=", __word_buffer) == 0) return success_empty_token(TOKEN_ASSIGN, out_token); 
                if (strcmp("==", __word_buffer) == 0) return success_empty_token(TOKEN_EQ, out_token);
                if (strcmp("+", __word_buffer) == 0) return success_empty_token(TOKEN_PLUS, out_token);

                switch (new_character)
                {
                    case '*':
                        return success_empty_token(TOKEN_MUL, out_token); 
                    case '(':
                        return success_empty_token(TOKEN_LEFT_PAREN, out_token); 
                    case ')':
                        return success_empty_token(TOKEN_RIGHT_PAREN, out_token); 
                    case '{':
                        return success_empty_token(TOKEN_LEFT_BRACE, out_token); 
                    case '}':
                        return success_empty_token(TOKEN_RIGHT_BRACE, out_token); 
                }
            }
        }

        // Pripisanie
        word_length++;
        if (word_length > word_buffer_size - 1) {
            word_buffer_size *= 2;
            char *tmp = realloc(__word_buffer, word_buffer_size);
            if (!tmp) {
                free(__word_buffer);
                return 99;
            }
            __word_buffer = tmp;
        }
        __word_buffer[word_length - 1] = new_character;
        __word_buffer[word_length] = '\0';
    }
    // TODO
    return 99;
}

TokenType *string_to_token_type(const char* str) {
    for (size_t i = 0; i < sizeof(tokenInfos)/sizeof(tokenInfos[0]); i++) {
        if (strcmp(tokenInfos[i].name, str) == 0) {
            return &tokenInfos[i].type;
        }
    }
    return NULL; // alebo iný default pre neznámy token
}

int success_empty_token(TokenType token_type, Token **out_token) {
    Token *token = get_empty_token(token_type);
    *out_token = token;
    free(__word_buffer);
    return 0;
}

int success_token(TokenType token_type, char *value, Token **out_token) {
    Token *token = get_token(token_type, value);
    *out_token = token;
    free(__word_buffer);
    return 0;
}