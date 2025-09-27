#include "token.h"

/**
 * @brief Lexical analyzer (tokenizer) for source code.
 *
 * Splits the input string into a sequence of tokens.
 *
 * @param source Input source code as a IFJ25 string.
 * @param out_tokens Pointer to an array of tokens (allocated by the function).
 * @param out_count Pointer to the number of tokens in the array.
 * @return LexerError Error code:
 *         - 0: success
 *         - 1: error while doing lexical analysys
 *         - 99: memory allocation failed
 *
 * @note Caller must free memory of tokens after use.
 */
int tokenize(const char* source, Token** out_tokens, int* out_count);
