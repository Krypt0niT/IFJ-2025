#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "../utilities/trim.h"

Token* get_simple_token(TokenType token_type);

int tokenize(const char *source, int source_length, Token ***out_tokens, int *out_count)
{
    unsigned int tokens_count = 0;
    // budem zvacsovat pri prekroceni a na konci nastavim presne
    int token_capacity = 10;
    Token **tokens = malloc(token_capacity * sizeof(Token *));

    int word_buffer_size = 10;
    char *word_buffer = malloc(sizeof(char) * word_buffer_size);

    int word_length = 0;

    for (int i = 0; i < source_length; i++) {

        char new_character = source[i];

        // tu sa mosi stat cela logika toho ze co to bolo pred medzerou
        if (new_character == ' ') {
            if (word_length > 0) {
                tokens_count++;
                Token *token = malloc(sizeof(Token));
                token->type = TOKEN_ID;

                token->value = malloc((word_length + 1) * sizeof(char));
                printf("deje sa kopirovanie do velkosti pamate: %i str: %s dlzka slova: %i\n", word_length +1, word_buffer, strlen(word_buffer));
                strcpy(token->value, word_buffer);
                tokens[tokens_count - 1] = token;

                printf(" type=%d, value=\"%s\"\n", token->type, token->value);

            }

            word_buffer[0] = '\0';
            word_length = 0;
            continue;
        }

        int special_character_found = 0;
        switch (new_character)
        {
            case '=':
                tokens_count++;
                tokens[tokens_count - 1] = get_simple_token(TOKEN_ASSIGN);
                special_character_found = 1;
                break;
            case '+':
                tokens_count++;
                tokens[tokens_count - 1] = get_simple_token(TOKEN_PLUS);
                special_character_found = 1;
                break;
            case '(':
                tokens_count++;
                tokens[tokens_count - 1] = get_simple_token(TOKEN_LEFT_PAREN);
                special_character_found = 1;
                break;
            
            default:
                break;
        }

        if (special_character_found) {
            continue;
        }

        word_length++;
        // -1 kvoli \0
        if (word_length > word_buffer_size - 1) {
            word_buffer_size *= 2;
            char *tmp = realloc(word_buffer, word_buffer_size);
            if (!tmp) {
                free(tokens);
                free(word_buffer);
                return 99;
            }
            word_buffer = tmp;
        }
        word_buffer[word_length - 1] = new_character;
        word_buffer[word_length] = '\0';
        
        char *trimmed_input = trim(word_buffer);

        if (strcmp(trimmed_input, "var") == 0) {
            tokens_count++;
            tokens[tokens_count - 1] = get_simple_token(TOKEN_VAR);      

            word_buffer[0] = '\0';   
            word_length = 0;       
        }
        
    }

    if (tokens_count == 0){
        free(tokens);
    }
    else {
        Token **tmp = realloc(tokens, tokens_count * sizeof(Token *));
        if (!tmp) {
            free(tokens);
            free(word_buffer);
            return 99;
        }
        tokens = tmp;
    }

    *out_count = tokens_count; 

    *out_tokens = tokens;
        printf("si kar tu je to v pohode %i\n", tokens);

    free(word_buffer);
    return 0;
}

void dispose_token(Token *token) {
    free(token->value);
    free(token);
}

Token* get_simple_token(TokenType token_type){
    Token *token = malloc(sizeof(Token));
    printf("teraz som alokoval token %d pre typ %i velkost %i \n", token, token_type, sizeof(Token));
    token->type = token_type;
    token->value = NULL;
    return token;
}
