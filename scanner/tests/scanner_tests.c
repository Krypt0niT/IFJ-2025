#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../scanner.h"
#include "inputs/scanner_valid_inputs.c"
#include "inputs/scanner_invalid_inputs.c"

void run_unit_tests();
void run_failing_unit_tests();

int run_scanner_test(const LexerTest* test, int index);
int run_failing_scanner_test(const LexerFailingTest* test, int index);

int compare_tokens(const Token* a, const Token* b);
void print_token(Token *token);

int main() {
    run_unit_tests();
    run_failing_unit_tests();
    return 0;
}

void run_unit_tests() {
    LexerTest tests[] = {
        test1,
        test2,
        test3,
        test4,
        test5,
        test6,
        test7,
        test8,
        test9,
        test10,
        test11,
        test12,
        test13,
        test14,
        test15,
        test16,
        test17,
        test18,
        test19,
        test20,
        test21,
        test22,
        test23,
        test24,
        test25,
        test26,
        test27,
        test28,
        test29
    };


    int total = sizeof(tests)/sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < total; i++) {
        if (run_scanner_test(&tests[i], i + 1)) passed++;
    }

    printf("Passed %d/%d scanner unit tests\n", passed, total);
}

void run_failing_unit_tests() {
    LexerFailingTest tests[] = {
        failing_test1,
        failing_test2,
        failing_test3,
        failing_test4,
        failing_test5,
        failing_test6,
        failing_test7,
        failing_test8,
        failing_test9,
        failing_test10,
        failing_test11,
        failing_test12,
        failing_test13,
        failing_test14,
        failing_test15,
        failing_test16,
        failing_test17,
        failing_test18,
        failing_test19,
        failing_test20
    };
    int total = sizeof(tests)/sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < total; i++) {
        if (run_failing_scanner_test(&tests[i], i + 1)) passed++;
    }

    printf("Passed %d/%d scanner failing unit tests\n", passed, total);
}

int run_scanner_test(const LexerTest* test, int index) {

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

        if (!compare_tokens(tok, &test->expected[i])) {
            printf("[%s] Token mismatch at index %d\n", test->name, i);
            printf("Expected: "); print_token(&test->expected[i]);
            printf("Got:      "); print_token(tok);
            success = 0;
            dispose_token(tok);
            break;
        }

        dispose_token(tok);
    }

    // skontrolujeme, či nie sú ďalšie neočakávané tokeny
    if (success) {
        Token *tok = NULL;
        if (get_next_token(&tok) == 0) {
            printf("[(%i) %s] Extra unexpected token after expected tokens:\n",index, test->name);
            print_token(tok);
            dispose_token(tok);
            success = 0;
        }
    }

    if (success) {
        printf("\033[0;32m[(%i) %s] Test passed!\033[0m\n", index, test->name);

    }

    fclose(f);
    return success;
}

int run_failing_scanner_test(const LexerFailingTest* test, int index) {

    FILE *f = tmpfile();
    if (!f) return 1;

    fwrite(test->source, 1, strlen(test->source), f);
    rewind(f);

    if (!f) {
        perror("fmemopen");
        return 0;
    }
    scanner_init(f);

    int fail = 0;
    for (int i = 0; i < test->expected_count; i++) {
        Token *tok = NULL;
        int result = get_next_token(&tok);
        if (result == 1) {
            fail = 1;
            break;
        }
        else if (result != 0) {
            fprintf(stderr, "Failing test failed with unexpected error.\n");
        }
        else {
            dispose_token(tok);
        }
    }

    if (fail) {
        printf("\033[0;32m[(%i) %s] Test error caught!\033[0m\n", index, test->name);

    }
    else {
        printf("[(%i) %s] Test did not caught error!\n", index, test->name);

    }

    fclose(f);
    return fail;
}

int compare_tokens(const Token* a, const Token* b) {
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