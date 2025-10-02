#include "../token.h"
#include <stdlib.h>

typedef struct {
    const char* name;      // názov testu
    const char* source;    // vstupný zdroj
    Token* expected;       // očakávané tokeny
    int expected_count;    // počet očakávaných tokenov
} LexerTest;


// --- TEST Simple assignment --- 
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

// --- TEST Variable names with nums --- 
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

// --- TEST Whitespace troubleshooting --- 
char *test3_name = "Whitespace troubleshooting";
char *test3_input = " \tvar  \tx=a +  10\n ";
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

// --- TEST Classic Numbers --- 
char *test4_name = "Classic Numbers";
char *test4_input = "   var num = 12 +10.25 \n";
Token test4_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "num"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "12"},
    {TOKEN_PLUS, NULL},
    {TOKEN_INT_LITERAL, "10.25"},
    {TOKEN_LINE_END, NULL}
};
int test4_expected_count = 7;
// ------------

// --- TEST Exponential nums --- 
char *test5_name = "Exponential nums";
char *test5_input = "var num = 1.12e5 + 0.55E+2 + 0.58e-4 \n";
Token test5_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "num"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "1.12e5"},
    {TOKEN_PLUS, NULL},
    {TOKEN_INT_LITERAL, "0.55E+2"},
    {TOKEN_PLUS, NULL},
    {TOKEN_INT_LITERAL, "0.58e-4"},
    {TOKEN_LINE_END, NULL}
};
int test5_expected_count = 7;
// ------------

// --- TEST Hex nums --- 
char *test6_name = "Hex nums";
char *test6_input = "var num = 0xdd + 0x1F + 0xAA\n";
Token test6_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "num"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "0xdd"},
    {TOKEN_PLUS, NULL},
    {TOKEN_INT_LITERAL, "0x1F"},
    {TOKEN_PLUS, NULL},
    {TOKEN_INT_LITERAL, "0xAA"},
    {TOKEN_LINE_END, NULL}
};
int test6_expected_count = 7;
// ------------

// --- TEST Multiple newlines collapse to single EOL ---
char *test7_name = "Multiple newlines collapse to single EOL";
char *test7_input = "\tvar a = 1\n\n\nvar b = 2\n";
Token test7_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "a"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "1"},
    {TOKEN_LINE_END, NULL},
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "b"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "2"},
    {TOKEN_LINE_END, NULL}
};
int test7_expected_count = 10;
// ------------

// --- TEST Keyword-like identifiers ---
char *test8_name = "Keyword-like identifiers";
char *test8_input = "var varx = 10\nifx1 = 20\n";
Token test8_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "varx"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "10"},
    {TOKEN_LINE_END, NULL},
    {TOKEN_ID, "ifx1"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "20"},
    {TOKEN_LINE_END, NULL}
};
int test8_expected_count = 9;

// --- TEST Leading zeros ---
char *test9_name = "Leading zeros";
char *test9_input = "var a = 012\n";
Token test9_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "a"},
    {TOKEN_ASSIGN, NULL},
    // ocakavana chyba
};
int test9_expected_count = 3;

// --- TEST Complex identifiers ---
char *test10_name = "Complex identifiers";
char *test10_input = "var _abc = 1\nvar XYZ_123 = 2\n";
Token test10_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "_abc"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "1"},
    {TOKEN_LINE_END, NULL},
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "XYZ_123"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "2"},
    {TOKEN_LINE_END, NULL}
};
int test10_expected_count = 10;

