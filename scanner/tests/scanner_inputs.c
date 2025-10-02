#include "../token.h"
#include <stdlib.h>

typedef struct {
    const char* name;      // názov testu
    const char* source;    // vstupný zdroj
    Token* expected;       // očakávané tokeny
    int expected_count;    // počet očakávaných tokenov
} LexerTest;


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
// ------------

// --- TEST 2 --- 
char *test2_name = "Variable names with nums";
char *test2_input = "var x_2 = a1 + 10\n";
Token test2_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "x_2"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_ID, "a1"},
    {TOKEN_PLUS, NULL},
    {TOKEN_INT_LITERAL, "10"},
    {TOKEN_LINE_END, NULL}
};
int test2_expected_count = 7;
// ------------

// --- TEST 3 --- 
char *test3_name = "Whitespace troubleshooting";
char *test3_input = "   var    x=a +  10\n ";
Token test3_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_ID, "a"},
    {TOKEN_PLUS, NULL},
    {TOKEN_INT_LITERAL, "10"},
    {TOKEN_LINE_END, NULL}
};
int test3_expected_count = 7;
// ------------