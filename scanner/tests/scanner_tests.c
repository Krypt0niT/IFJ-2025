#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../token.h"
#include "../scanner.h"

typedef struct {
    const char* name;      // názov testu
    const char* source;    // vstupný zdroj
    int source_length;     // dlzka vstupu
    Token* expected;       // očakávané tokeny
    int expected_count;    // počet očakávaných tokenov
} LexerTest;

int runLexerTest(const LexerTest* test);
int compareTokens(const Token* a, const Token* b);
void print_tokens(Token **tokens, int length);

// --- TEST 1 --- 
char *test1_name = "Simple assignment";
char *test1_input = "var x = y + 10\n";
Token test1_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_ID, "y"},
    {TOKEN_PLUS, NULL},
    {TOKEN_INT_LITERAL, "10"},
    {TOKEN_LINE_END, NULL}
};
int test1_count = 7;

int main() {

    LexerTest tests[] = {
        // TEST 1 Job
        {test1_name, test1_input, (int)strlen(test1_input), test1_expectation, test1_count},
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
    Token** tokens = NULL;
    int count = 0;
    if (tokenize(test->source, test->source_length, &tokens, &count) != 0) {
        printf("[%s] Lexer error!\n", test->name);
        return 0;
    }
    printf("result tokens: %i\n", tokens);
    print_tokens(tokens, count);

    if (count != test->expected_count) {
        printf("[%s] Token count mismatch (%d != %d)\n", test->name, count, test->expected_count);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        if (!compareTokens(tokens[i], &test->expected[i])) {
            printf("[%s] Token mismatch at index %d\n", test->name, i);
            return 0;
        }
    }

    printf("[%s] Test passed!\n", test->name);

    // uvolnenie pamate
    for (int i = 0; i < count; i++) dispose_token(tokens[i]);
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

void print_tokens(Token **tokens, int length) {
    for (int i = 0; i < length; i++) {
        if (tokens[i] == NULL) {
            continue;
        }
        printf("[%d] type=%d, value=\"%s\"\n",
               i,
               tokens[i]->type,
               "zatial nic");
    }
}