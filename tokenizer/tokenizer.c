#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

Token* get_simple_token(TokenType token_type);

int tokenize(const char *source, int source_length, Token **out_tokens, int *out_count)
{
    int tokens_count = 0;
    // budem zvacsovat pri prekroceni a na konci nastavim presne
    int token_capacity = 10;
    out_tokens = malloc(token_capacity * sizeof(Token *));

    int word_buffer_size = 10;
    char *word_buffer = malloc(sizeof(char) * word_buffer_size);

    int word_length = 0;

    for (int i = 0; i < source_length; i++) {

        char new_character = source[i];
        
        word_length++;
        // -1 kvoli \0
        if (word_length > word_buffer_size - 1) {
            word_buffer_size *= 2;
            char *tmp = realloc(word_buffer, word_buffer_size);
            if (!tmp) {
                free(out_tokens);
                free(word_buffer);
                return 99;
            }
            word_buffer = tmp;
        }
        word_buffer[word_length - 1] = new_character;
        word_buffer[word_length] = '\0';
        
        printf("toto: %s\n",word_buffer);

        switch (new_character)
        {
            case '(':
                tokens_count++;
                out_tokens[tokens_count - 1] = get_simple_token(TOKEN_LEFT_PAREN);
                break;
            
            default:
                break;
        }
    }

    out_tokens = realloc(out_tokens, tokens_count * sizeof(Token *));
    return 0;
}

void dispose_token(Token *token) {
    free(token->value);
    free(token);
}

Token* get_simple_token(TokenType token_type){
    Token *token = malloc(sizeof(Token));
    token->type = token_type;
    return token;
}
