#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../scanner.h"
#include "scanner_inputs.c"

int runLexerTest(const LexerTest* test);
int compareTokens(const Token* a, const Token* b);
void print_token(Token *token);

int main() {

    LexerTest tests[] = {
        {test1_name, test1_input, test1_expectation, test1_expected_count},
        {test2_name, test2_input, test2_expectation, test2_expected_count},
        {test3_name, test3_input, test3_expectation, test3_expected_count},
        {test4_name, test4_input, test4_expectation, test4_expected_count},
        {test5_name, test5_input, test5_expectation, test5_expected_count},
        {test6_name, test6_input, test6_expectation, test6_expected_count},
        {test7_name, test7_input, test7_expectation, test7_expected_count},
        {test8_name, test8_input, test8_expectation, test8_expected_count},
        {test9_name, test9_input, test9_expectation, test9_expected_count},
        {test10_name, test10_input, test10_expectation, test10_expected_count},
        {test11_name, test11_input, test11_expectation, test11_expected_count},
        {test12_name, test12_input, test12_expectation, test12_expected_count},
        {test13_name, test13_input, test13_expectation, test13_expected_count},
        {test14_name, test14_input, test14_expectation, test14_expected_count},
        {test15_name, test15_input, test15_expectation, test15_expected_count},
        {test16_name, test16_input, test16_expectation, test16_expected_count},
        {test17_name, test17_input, test17_expectation, test17_expected_count},
        {test18_name, test18_input, test18_expectation, test18_expected_count},
        {test19_name, test19_input, test19_expectation, test19_expected_count},
        {test20_name, test20_input, test20_expectation, test20_expected_count},
        {test21_name, test21_input, test21_expectation, test21_expected_count},
        {test22_name, test22_input, test22_expectation, test22_expected_count},
        {test23_name, test23_input, test23_expectation, test23_expected_count},
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
    if (!f) return 1;

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