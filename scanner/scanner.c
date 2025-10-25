#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
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
    {TOKEN_NULL, "Null"},
    {TOKEN_RETURN, "return"},
    {TOKEN_VAR, "var"},
    {TOKEN_WHILE, "while"},
    {TOKEN_IFJ, "Ifj"},
    {TOKEN_STATIC, "static"},
    {TOKEN_IMPORT, "import"},
    {TOKEN_FOR, "for"},
    {TOKEN_NUM, "Num"},
    {TOKEN_STRING, "String"},
    {TOKEN_NULL_LITERAL, "null"},
};

typedef enum {
    STATE_NONE,
    STATE_TEXT,
    STATE_NUM,
    STATE_SYMBOL,
    STATE_STRING

} StateType;

TokenType* string_to_token_type(char* str);
TokenType get_num_literal_type(char* str);
Token* get_empty_token(TokenType token_type);
Token* get_token(TokenType token_type, char *value);
int success_empty_token(TokenType token_type, Token **out_token);
int success_token(TokenType token_type, char *value, Token **out_token);
int is_valid_text_symbol(char c);
int is_valid_num_symbol(char c);
int is_operator_char(char c);
int contains(char *array, char a);
int get_num_format(char *array, TokenType *out_token);

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

// TODO: remove later.
unsigned int max_word_length_for_tests = 100; 
bool is_comment = false;

FILE *__input_file = NULL;
char *__word_buffer = NULL;

void scanner_init(FILE *input_file) {
    __input_file = input_file;
}

int get_next_token(Token **out_token) {
    if (__input_file == NULL) {
        // TODO zistit typ chyby
        return 99;
    }
    is_comment = false;

    int word_buffer_size = 10;
    __word_buffer = calloc(word_buffer_size, sizeof(char));

    StateType automat_state = STATE_NONE;
    int word_length = 0;
    int c;

    while ((c = getc(__input_file)) != EOF) {

        //printf("dlzka:%i state:%i char:'%c' word:'%s'\n", word_length, automat_state, c, __word_buffer);

        //TODO: remove later.
        if (word_length > max_word_length_for_tests) {
            fprintf(stderr, "prekroceny limit bufferu.\n");
            return 99;
        }

        char new_character = c;

        // ignored characters
        if (new_character == ',') continue;

        // AGRESIVNE ZNAKY
        if (word_length == 0) {
            if (new_character == '\n') {
                while ((c = getc(__input_file)) == '\n');
                ungetc(c, __input_file);
                return success_empty_token(TOKEN_LINE_END, out_token);
            }
            if (new_character == '(') return success_empty_token(TOKEN_LEFT_PAREN, out_token);
            if (new_character == ')') return success_empty_token(TOKEN_RIGHT_PAREN, out_token);
            if (new_character == '{') return success_empty_token(TOKEN_LEFT_BRACE, out_token);
            if (new_character == '}') return success_empty_token(TOKEN_RIGHT_BRACE, out_token);
        }

        // Defines how words start
        if (automat_state == STATE_NONE && !isspace(new_character)) {
            if (isalpha(new_character) != 0 || new_character == '_') automat_state = STATE_TEXT;
            else if (isdigit(new_character)) automat_state = STATE_NUM;
            else if (new_character == '"') automat_state = STATE_STRING;
            else if (is_operator_char(new_character)) automat_state = STATE_SYMBOL;
            else return 1;
        }
        
        if (automat_state == STATE_TEXT) {
            if (!is_valid_text_symbol(new_character)) {
                ungetc(new_character, __input_file);

                TokenType *reserved_word = string_to_token_type(__word_buffer);
                if (reserved_word != NULL) {
                    return success_empty_token(*reserved_word, out_token); 
                }

                // Global indentificator
                if (strncmp("__", __word_buffer, 2) == 0) {
                    return success_token(TOKEN_GLOBAL_VAR, __word_buffer, out_token); 
                }
                return success_token(TOKEN_ID, __word_buffer, out_token);
            }
        }

        if (automat_state == STATE_NUM) {
            if (!is_valid_num_symbol(new_character)) {
                ungetc(new_character, __input_file);
                //TODO: return ci chyba alebo dobre format
                TokenType token_type;
                int invalid = get_num_format(__word_buffer, &token_type);
                if (invalid) return 1;

                return success_token(token_type, __word_buffer, out_token); 
            }
        }

        if (automat_state == STATE_SYMBOL) {
            if (isdigit(new_character) != 0 || isalpha(new_character) != 0 || new_character == ' ') {
                ungetc(new_character, __input_file);
                //TODO: opravit
                if (strcmp("=", __word_buffer) == 0) return success_empty_token(TOKEN_ASSIGN, out_token); 
                if (strcmp("==", __word_buffer) == 0) return success_empty_token(TOKEN_EQ, out_token);
                if (strcmp("!=", __word_buffer) == 0) return success_empty_token(TOKEN_NE, out_token);
                if (strcmp("<", __word_buffer) == 0) return success_empty_token(TOKEN_LT, out_token);
                if (strcmp("<=", __word_buffer) == 0) return success_empty_token(TOKEN_LE, out_token);
                if (strcmp(">", __word_buffer) == 0) return success_empty_token(TOKEN_GT, out_token);
                if (strcmp(">=", __word_buffer) == 0) return success_empty_token(TOKEN_GE, out_token);
                if (strcmp("+", __word_buffer) == 0) return success_empty_token(TOKEN_PLUS, out_token);
                if (strcmp("-", __word_buffer) == 0) return success_empty_token(TOKEN_MINUS, out_token);
                if (strcmp("/", __word_buffer) == 0) return success_empty_token(TOKEN_DIV, out_token);
                if (strcmp("*", __word_buffer) == 0) return success_empty_token(TOKEN_MUL, out_token);

                // TODO !!
                if (strcmp("//", __word_buffer) == 0) is_comment = true;
                if (strcmp("/*", __word_buffer) == 0) is_comment = true;
                if (strcmp("*/", __word_buffer) == 0) is_comment = true;
            }
        }

        // TODO: remove
        if (automat_state == STATE_STRING) {
            fprintf(stderr, "Strings not implemented.\n");
            return 98; // not implemented
        }

        if (is_comment) {
            if (strcmp(__word_buffer, "//") == 0) {
                while ((c = getc(__input_file)) != '\n' && c != EOF);
                if (c == '\n') ungetc(c, __input_file);
                is_comment = false;
                word_length = 0;
                __word_buffer[0] = '\0';
                automat_state = STATE_NONE;
                continue;
            }
            if (strcmp(__word_buffer, "/*") == 0) {
                int prev = 0;
                while ((c = getc(__input_file)) != EOF) {
                    if (prev == '*' && c == '/') break;
                    prev = c;
                }

                // po ukonceni komentu preskoc jeden pripadny '\n'
                c = getc(__input_file);
                if (c != EOF && c != '\n')
                    ungetc(c, __input_file);

                is_comment = false;
                word_length = 0;
                __word_buffer[0] = '\0';
                automat_state = STATE_NONE;
                continue;
            }
            return 1;
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

        __word_buffer = trim(__word_buffer);
        word_length = strlen(__word_buffer);

    }
    // TODO
    return 99;
}

TokenType *string_to_token_type(char* str) {
    for (size_t i = 0; i < sizeof(tokenInfos)/sizeof(tokenInfos[0]); i++) {
        if (strcmp(tokenInfos[i].name, str) == 0) {
            return &tokenInfos[i].type;
        }
    }
    return NULL;
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

int is_valid_text_symbol(char c) {
    if (isdigit(c) != 0 || isalpha(c) != 0 || c == '_') return 1;
    return 0;
}

// TODO separate valid sybols
int is_valid_num_symbol(char c) {
    if (isdigit(c) || 
        isalpha(c) ||
        c == '+' || 
        c == '-' ||
        c == '.'
    ) 
    return 1;
    return 0;

    /*c == 'e' || 
        c == 'E' || 
        c == '+' || 
        c == '-' ||
        c == '.' ||
        c == 'x' ||
        c == 'a' ||
        c == 'b' ||
        c == 'c' ||
        c == 'd' ||
        c == 'e' ||
        c == 'f' ||
        c == 'A' ||
        c == 'B' ||
        c == 'C' ||
        c == 'D' ||
        c == 'E' ||
        c == 'F'*/
}

// TODO funkcionalita skontrolovania nevalidneho vstuppu cisla .h?
TokenType get_num_literal_type(char* str) {
    if (contains(str, '.') || contains(str, 'e') || contains(str, 'E')) {
        return TOKEN_FLOAT_LITERAL;
    }
    if (contains(str, 'x')) {
        return TOKEN_HEX_LITERAL;
    }

    return TOKEN_INT_LITERAL;
}

int contains(char *array, char a) {
    int length = strlen(array);
    for (int i = 0; i < length; i++)
    {
        if (array[i] == a) return 1;
    }
    return 0;
}

int is_operator_char(char c) {
    return c == '=' || c == '/' || c == '*' || c == '-' ||
           c == '+' || c == '!' || c == '<' || c == '>';
}

// funkcia bude overovat platnost formatu cisla
// pri neplatnom cisle vrati nenulovy vystup 
// na out token sa zavedie platny typ ciselneho literalu - hex, float, esp, int
// priklad -> *out_token = TOKEN_INT_LITERAL;
int get_num_format(char *array, TokenType *out_token) {
    unsigned len = strlen(array);
    if(array[0] == '0' && array[1] == '0')
        return 1;
    if(len == 4 && array[0] == '0' && (array[1] == 'x' || array[1] == 'X')){
        for(unsigned i = 2; i< strlen(array); i++){
            if(!((array[i] >= 'A' && array[i] <= 'F') || (array[i] >= 'a' && array[i] <= 'f') || (array[i] >= '0' && array[i] <= '9')))
                return 1;
        }
        *out_token = TOKEN_HEX_LITERAL;
        return 0;
    }

    // [celá_časť].[desatinná_časť]e[+/-][exponent]
    // [celá_časť]e[+/-][exponent]
    // counters
    int has_dot = 0;
    int has_exp = 0;
    int exp_sign_allowed = 0;
    int exp_digits = 0;

    for (unsigned i = 0; i < len; i++) {
        char c = array[i];

        if (isdigit((unsigned char)c)) {
            if (has_exp) exp_digits++;
            continue;
        }

        // Bodka
        if (c == '.') {
            if (has_dot || has_exp) return 1;
            has_dot = 1;
            continue;
        }

        // Exponent
        if (c == 'e' || c == 'E') {
            if (has_exp) return 1; // viac exponentov
            has_exp = 1;
            exp_sign_allowed = 1; // po e môže byť + alebo -
            exp_digits = 0;
            continue;
        }

        // Znamienko po exponente
        if ((c == '+' || c == '-') && exp_sign_allowed) {
            exp_sign_allowed = 0;
            continue;
        }

        // ak sa sem dostane, je to neplatny znak
        return 1;
    }

    if (has_exp && exp_digits == 0) return 1;

    else if (has_dot || has_exp) *out_token = TOKEN_FLOAT_LITERAL;
    else *out_token = TOKEN_INT_LITERAL;
    return 0;
    
}