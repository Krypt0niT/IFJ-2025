#include "token.h"
#include <stdio.h>

/**
 * @brief Initializes the scanner with the given input file.
 *
 * @param input_file Pointer to an open input file.
 */
void scanner_init(FILE *input_file);

/**
 * @brief Retrieves the next token from the input file.
 *
 * The function attempts to read the next token from the input stream.  
 * If the file is invalid, not specified, or the end of file has been reached, 
 * the function will return `NULL` in `out_token`.  
 *
 * The caller is responsible for freeing the allocated token using
 * dispose_token().
 *
 * @param[out] out_token Pointer to a variable where the allocated token will be stored.
 * @return 0 if a token was successfully read,  
 *         1 if a scanner error occurred,  
 *         99 if another error occurred (e.g., memory allocation failure).
 */
int get_next_token(Token **out_token);

/**
 * @brief Releases all allocated resources of a token.
 *
 * This function must be called by the caller for every token returned
 * by get_next_token().
 *
 * @param token Pointer to the token to be freed.
 */
void dispose_token(Token *token);
