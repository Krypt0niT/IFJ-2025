#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../token.h"
#include "../scanner.h"

typedef struct {
    const char* name;      // názov testu
    const char* source;    // vstupný zdroj
    Token* expected;       // očakávané tokeny
    int expected_count;    // počet očakávaných tokenov
} LexerTest;

int runLexerTest(const LexerTest* test);
int compareTokens(const Token* a, const Token* b);
void print_token(Token *token);

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
int test1_expected_count = 7;

int main() {

    LexerTest tests[] = {
        // TEST 1 Job
        {test1_name, test1_input, test1_expectation, test1_expected_count},
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

    FILE *f = tmpfile();
    if (!f) return NULL;

    fwrite(test->source, 1, strlen(test->source), f);
    rewind(f);

    if (!f) {
        perror("fmemopen");
        return 0;
    }
    scanner_init(f);

    int success = 1; // predpokladáme úspech

    for (int i = 0; i < test->expected_count; i++) {
        Token *tok = NULL;
        if (get_next_token(&tok) != 0) {
            printf("[%s] Unexpected end of input at token %d\n", test->name, i);
            success = 0;
            break;
        }

        if (!compareTokens(tok, &test->expected[i])) {
            printf("[%s] Token mismatch at index %d\n", test->name, i);
            printf("Expected: "); print_token(&test->expected[i]);
            printf("Got:      "); print_token(tok);
            success = 0;
            dispose_token(tok);
            break;
        }

        dispose_token(tok); // uvoľníme ihneď
    }

    // skontrolujeme, či nie sú ďalšie neočakávané tokeny
    if (success) {
        Token *tok = NULL;
        if (get_next_token(&tok) == 0) {
            printf("[%s] Extra unexpected token after expected tokens:\n", test->name);
            print_token(tok);
            dispose_token(tok);
            success = 0;
        }
    }

    if (success) {
        printf("[%s] Test passed!\n", test->name);
    }

    fclose(f);
    return success;
}

int compareTokens(const Token* a, const Token* b) {
    if (a->type != b->type) return 0;
    if ((a->value == NULL && b->value != NULL) || (a->value != NULL && b->value == NULL))
        return 0;
    if (a->value && b->value && strcmp(a->value, b->value) != 0)
        return 0;
    return 1;
}

void print_token(Token *token) {
    if (token == NULL) {
        return;
    }
    printf("type=%d, value=\"%s\"\n",
            token->type,
            token->value);
}