#include "token.h"

/**
 * @brief Lexical analyzer (tokenizer) for source code.
 *
 * Splits the input string into a sequence of tokens.
 *
 * This function processes exactly `source_length` characters from the input,
 * so it works correctly even if the input contains null bytes ('\0').
 *
 * @param source Pointer to the input source code as a string or buffer.
 * @param source_length Number of characters in the input buffer to process.
 * @param out_tokens Pointer to an array of tokens (allocated by the function).
 * @param out_count Pointer to an integer where the number of generated tokens will be stored.
 * @return LexerError Error code:
 *         - 0: success
 *         - 1: error during lexical analysis
 *         - 99: memory allocation failed
 *
 * @note The caller is responsible for freeing the memory allocated for the tokens array.
 */
int tokenize(const char* source, int source_length, Token** out_tokens, int* out_count);


/**
 * @brief Frees memory used by a single Token.
 *
 * This function releases any dynamically allocated memory
 * inside the Token, such as the lexeme stored in `value`.
 *
 * @param token Pointer to the Token to dispose.
 */
void dispose_token(Token *token);
