#include "../../token.h"
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
    {TOKEN_FLOAT_LITERAL, "10.25"},
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
    {TOKEN_FLOAT_LITERAL, "1.12e5"},
    {TOKEN_PLUS, NULL},
    {TOKEN_FLOAT_LITERAL, "0.55E+2"},
    {TOKEN_PLUS, NULL},
    {TOKEN_FLOAT_LITERAL, "0.58e-4"},
    {TOKEN_LINE_END, NULL}
};
int test5_expected_count = 9;
// ------------

// --- TEST Hex nums --- 
char *test6_name = "Hex nums";
char *test6_input = "var num = 0xdd + 0x1F + 0xAA\n";
Token test6_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "num"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_HEX_LITERAL, "0xdd"},
    {TOKEN_PLUS, NULL},
    {TOKEN_HEX_LITERAL, "0x1F"},
    {TOKEN_PLUS, NULL},
    {TOKEN_HEX_LITERAL, "0xAA"},
    {TOKEN_LINE_END, NULL}
};
int test6_expected_count = 9;
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
char *test8_input = "var var_x = 10\nifclassx1 = 20\n";
Token test8_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "var_x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "10"},
    {TOKEN_LINE_END, NULL},
    {TOKEN_ID, "ifclassx1"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "20"},
    {TOKEN_LINE_END, NULL}
};
int test8_expected_count = 9;

// --- TEST Function call with parentheses ---
char *test9_name = "Function call with parentheses";
char *test9_input = "var x = func(a, b)\n";
Token test9_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_ID, "func"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "a"},
    {TOKEN_ID, "b"},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL}
};
int test9_expected_count = 9;
// ------------

// --- TEST Complex identifiers ---
char *test10_name = "Complex identifiers";
char *test10_input = "var _abc = 1\nvar XYZ__123 = 2\n";
Token test10_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "_abc"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "1"},
    {TOKEN_LINE_END, NULL},
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "XYZ__123"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "2"},
    {TOKEN_LINE_END, NULL}
};
int test10_expected_count = 10;

char *test11_name = "String literals";
char *test11_input = "var s = \"Ahoj\\n\\\"Sve'te \\\\\\x22\"\n";     // "\\" = "\"        "\x22" = 34 = "
Token test11_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "s"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_STRING_LITERAL, "Ahoj\n\"Sve'te \\\""},
    {TOKEN_LINE_END, NULL}
};
int test11_expected_count = 5;

char *test12_name = "Empty string and string with \n";
char *test12_input = "var s = \"\"\nvar space = \"\\n\"\n";
Token test12_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "s"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_STRING_LITERAL, ""},
    {TOKEN_LINE_END, NULL},
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "space"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_STRING_LITERAL, "\n"},
    {TOKEN_LINE_END, NULL}
};
int test12_expected_count = 10;

// --- TEST Arithmetic operators ---
char *test13_name = "Arithmetic operators";
char *test13_input = "var x = 10 + 2 - 3 * 4 / 5\n";
Token test13_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "10"},
    {TOKEN_PLUS, NULL},
    {TOKEN_INT_LITERAL, "2"},
    {TOKEN_MINUS, NULL},
    {TOKEN_INT_LITERAL, "3"},
    {TOKEN_MUL, NULL},
    {TOKEN_INT_LITERAL, "4"},
    {TOKEN_DIV, NULL},
    {TOKEN_INT_LITERAL, "5"},
    {TOKEN_LINE_END, NULL}
};
int test13_expected_count = 13;
// ------------


// --- TEST Complex expression with parentheses ---
char *test14_name = "Complex expression with parentheses";
char *test14_input = "var result = ((a + b) * (c - d)) / e\n";
Token test14_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "result"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "a"},
    {TOKEN_PLUS, NULL},
    {TOKEN_ID, "b"},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_MUL, NULL},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "c"},
    {TOKEN_MINUS, NULL},
    {TOKEN_ID, "d"},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_DIV, NULL},
    {TOKEN_ID, "e"},
    {TOKEN_LINE_END, NULL}
};
int test14_expected_count = 19;
// ------------

// --- TEST Class ---
char *test15_name = "Class keyword and Braces with newlines";
char *test15_input = "class MyClass\n{\n}\n";
Token test15_expectation[] = {
    {TOKEN_CLASS, NULL},
    {TOKEN_ID, "MyClass"},
    {TOKEN_LINE_END, NULL},
    {TOKEN_LEFT_BRACE, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_RIGHT_BRACE, NULL},
    {TOKEN_LINE_END, NULL}
};
int test15_expected_count = 7;


// --- TEST If ---
char *test16_name = "If keyword, IS literal and String, Num token";
char *test16_input = "if (x is String)\n{\n}\nif(s is Num)\n"; 
Token test16_expectation[] = {
    {TOKEN_IF, NULL},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_IS, NULL},
    {TOKEN_STRING, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_LEFT_BRACE, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_RIGHT_BRACE, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IF, NULL},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "s"},
    {TOKEN_IS, NULL},
    {TOKEN_NUM, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
};
int test16_expected_count = 18;

// --- TEST Global var ---
char *test17_name = "Global var";
char *test17_input = "var __g = 42\n";
Token test17_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_GLOBAL_VAR, "__g"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "42"},
    {TOKEN_LINE_END, NULL}
};
int test17_expected_count = 5;

// --- TEST Else keyword ---
char *test18_name = "(18) Else keyword";
char *test18_input = "if (x) { } else { }\n";
Token test18_expectation[] = {
    {TOKEN_IF, NULL},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LEFT_BRACE, NULL},
    {TOKEN_RIGHT_BRACE, NULL},
    {TOKEN_ELSE, NULL},
    {TOKEN_LEFT_BRACE, NULL},
    {TOKEN_RIGHT_BRACE, NULL},
    {TOKEN_LINE_END, NULL}
};
int test18_expected_count = 10;
// ------------

// --- TEST Null keyword and literal ---
char *test19_name = "Null keyword and literal";
char *test19_input = "var x = null\nif (y is Null) { }\n";
Token test19_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_NULL_LITERAL, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IF, NULL},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "y"},
    {TOKEN_IS, NULL},
    {TOKEN_NULL, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LEFT_BRACE, NULL},
    {TOKEN_RIGHT_BRACE, NULL},
    {TOKEN_LINE_END, NULL}
};
int test19_expected_count = 14;
// ------------

// --- TEST Return keyword ---
char *test20_name = "Return keyword";
char *test20_input = "return foo(only_par,\n only_par)\nreturn x + y\nreturn\n";
Token test20_expectation[] = {
    {TOKEN_RETURN, NULL},
    {TOKEN_ID, "foo"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "only_par"},
    {TOKEN_ID, "only_par"},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_RETURN, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_PLUS, NULL},
    {TOKEN_ID, "y"},
    {TOKEN_LINE_END, NULL},
    {TOKEN_RETURN, NULL},
    {TOKEN_LINE_END, NULL}
};
int test20_expected_count = 14;
// ------------

// --- TEST While keyword ---
char *test21_name = "While keyword";
char *test21_input = "while (x >\n 0) { x =\n x -\n 1 }\n";
Token test21_expectation[] = {
    {TOKEN_WHILE, NULL},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_GT, NULL},
    {TOKEN_INT_LITERAL, "0"},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LEFT_BRACE, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_MINUS, NULL},
    {TOKEN_INT_LITERAL, "1"},
    {TOKEN_RIGHT_BRACE, NULL},
    {TOKEN_LINE_END, NULL}
};
int test21_expected_count = 14;
// ------------

// --- TEST Import keyword ---
char *test22_name = "Import & for keyword";
char *test22_input = "import \"ifj25\" for Ifj\n";
Token test22_expectation[] = {
    {TOKEN_IMPORT, NULL},
    {TOKEN_STRING_LITERAL, "ifj25"},
    {TOKEN_FOR, NULL},
    {TOKEN_IFJ, NULL},
    {TOKEN_LINE_END, NULL}
};
int test22_expected_count = 5;
// ------------

// --- TEST Static keyword ---
char *test23_name = "Static keyword";
char *test23_input = "static main() { }\nstatic func(\nx){}\n";
Token test23_expectation[] = {
    {TOKEN_STATIC, NULL},
    {TOKEN_ID, "main"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LEFT_BRACE, NULL},
    {TOKEN_RIGHT_BRACE, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_STATIC, NULL},
    {TOKEN_ID, "func"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LEFT_BRACE, NULL},
    {TOKEN_RIGHT_BRACE, NULL},
    {TOKEN_LINE_END, NULL}
};
int test23_expected_count = 16;
// ------------

// --- TEST Ifj vstavane funkcie ---
char *test24_name = "Ifj vstavane funkcie";
char *test24_input = 
    "Ifj.write(x)\n"
    "Ifj .  read_num()\n"
    "Ifj.\tread_str()\n"
    "\n"
    "Ifj.floor()\n"
    "Ifj.str()\n"
    "Ifj.\n"
    "length()\n"
    "Ifj.substring\n"
    "Ifj.\n"
    "\n"
    "strcmp(\n"
    ")\n"
    "Ifj.\t\tord()\n"
    "Ifj.chr()\n";
    Token test24_expectation[] = {
    {TOKEN_IFJ, "write"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IFJ, "read_num"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IFJ, "read_str"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IFJ, "floor"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IFJ, "str"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IFJ, "length"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IFJ, "substring"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IFJ, "strcmp"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IFJ, "ord"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL},
    {TOKEN_IFJ, "chr"},
    {TOKEN_LEFT_PAREN, NULL},
    {TOKEN_RIGHT_PAREN, NULL},
    {TOKEN_LINE_END, NULL} 
};
int test24_expected_count = 41;
// ------------

// --- TEST Relational operators with numbers ---
char *test25_name = "Relational operators with numbers";
char *test25_input = "1 < 2 3.5 > 2.1 10 <= 10 5 >= 5 0 == 0 1 != 0\n";
Token test25_expectation[] = {
    {TOKEN_INT_LITERAL, "1"},
    {TOKEN_LT, NULL},
    {TOKEN_INT_LITERAL, "2"},
    {TOKEN_FLOAT_LITERAL, "3.5"},
    {TOKEN_GT, NULL},
    {TOKEN_FLOAT_LITERAL, "2.1"},
    {TOKEN_INT_LITERAL, "10"},
    {TOKEN_LE, NULL},
    {TOKEN_INT_LITERAL, "10"},
    {TOKEN_INT_LITERAL, "5"},
    {TOKEN_GE, NULL},
    {TOKEN_INT_LITERAL, "5"},
    {TOKEN_INT_LITERAL, "0"},
    {TOKEN_EQ, NULL},
    {TOKEN_INT_LITERAL, "0"},
    {TOKEN_INT_LITERAL, "1"},
    {TOKEN_NE, NULL},
    {TOKEN_INT_LITERAL, "0"},
    {TOKEN_LINE_END, NULL}
};
int test25_expected_count = 19;
// ------------

// --- TEST Multiline string literal ---
char *test26_name = "Multiline string literal";
char *test26_input = "var x = \"\"\"A\nhoj s\\x22\"vete\n\"\"\"\n";
Token test26_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_STRING_LITERAL, "A\nhoj s\\x22\"vete\n"},
    {TOKEN_LINE_END, NULL}
};
int test26_expected_count = 5;
// ------------

// --- TEST Line comment ---
char *test27_name = "(27) Line comment";
char *test27_input = "var x = 1 // toto je komentar\nvar y = 2\n";
Token test27_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "1"},
    {TOKEN_LINE_END, NULL},
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "y"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "2"},
    {TOKEN_LINE_END, NULL}
};
int test27_expected_count = 10;
// ------------

// --- TEST Block comment single line ---
char *test28_name = "Block comment single line";
char *test28_input = "var x = 1 /* komentar */ var y = 2\n";
Token test28_expectation[] = {
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "x"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "1"},
    {TOKEN_VAR, NULL},
    {TOKEN_ID, "y"},
    {TOKEN_ASSIGN, NULL},
    {TOKEN_INT_LITERAL, "2"},
    {TOKEN_LINE_END, NULL}
};
int test28_expected_count = 9;
// ------------

// --- TEST Block comment multiline ---
char *test29_name = "Block comment multiline";
char *test29_input = "var a = 1\n/* komentar\n na viac riadkov */\nvar b = 2\n";
Token test29_expectation[] = {
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
int test29_expected_count = 10;
// ------------
