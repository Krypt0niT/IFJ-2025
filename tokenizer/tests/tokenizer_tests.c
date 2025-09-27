#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../token.h"
#include "../tokenizer.h"

typedef struct {
    const char* name;      // názov testu
    const char* source;    // vstupný zdroj
    Token* expected;       // očakávané tokeny
    int expected_count;    // počet očakávaných tokenov
} LexerTest;

int runLexerTest(const LexerTest* test);
int compareTokens(const Token* a, const Token* b);

int main() {
    // definicia testu 1
    Token test1_tokens[] = {
        {TOKEN_VAR, "var"},
        {TOKEN_ID, "x"},
        {TOKEN_ASSIGN, "="},
        {TOKEN_ID, "y"},
        {TOKEN_PLUS, "+"},
        {TOKEN_INT_LITERAL, "10"},
        {TOKEN_LINE_END, "\n"}
    };

    LexerTest tests[] = {
        {"Simple assignment", "var x = y + 10\n", test1_tokens, 7},
        // tu môzes pridat dalsie testy
    };

    int total = sizeof(tests)/sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < total; i++) {
        if (runLexerTest(&tests[i])) passed++;
    }

    printf("Passed %d/%d tests\n", passed, total);
    return 0;
}

int runLexerTest(const LexerTest* test) {
    Token* tokens = NULL;
    int count = 0;

    if (tokenize(test->source, &tokens, &count) != 0) {
        printf("[%s] Lexer error!\n", test->name);
        return 0;
    }

    if (count != test->expected_count) {
        printf("[%s] Token count mismatch (%d != %d)\n", test->name, count, test->expected_count);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        if (!compareTokens(&tokens[i], &test->expected[i])) {
            printf("[%s] Token mismatch at index %d\n", test->name, i);
            return 0;
        }
    }

    printf("[%s] Test passed!\n", test->name);

    // uvolnenie pamate
    for (int i = 0; i < count; i++) free(tokens[i].value);
    free(tokens);

    return 1;
}

int compareTokens(const Token* a, const Token* b) {
    if (a->type != b->type) return 0;
    if ((a->value == NULL && b->value != NULL) || (a->value != NULL && b->value == NULL))
        return 0;
    if (a->value && b->value && strcmp(a->value, b->value) != 0)
        return 0;
    return 1;
}
