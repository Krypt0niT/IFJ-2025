#include "../../token.h"
#include <stdlib.h>

typedef struct {
    const char* name;      // názov testu
    const char* source;    // vstupný zdroj
    Token* expected;       // očakávané tokeny
    int expected_count;    // počet očakávaných tokenov
} LexerTest;

// --- TEST Simple assignment --- 
LexerTest test1 = {
    "Simple assignment",
    "var x = y + 10\n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "x"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_ID, "y"},
        {TOKEN_PLUS, NULL},
        {TOKEN_INT_LITERAL, "10"},
        {TOKEN_LINE_END, NULL}
    },
    7
};

// --- TEST Variable names with nums --- 
LexerTest test2 = {
    "Variable names with nums",
    "var x_2 = a1 + 10\n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "x_2"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_ID, "a1"},
        {TOKEN_PLUS, NULL},
        {TOKEN_INT_LITERAL, "10"},
        {TOKEN_LINE_END, NULL}
    },
    7
};

// --- TEST Whitespace troubleshooting --- 
LexerTest test3 = {
    "Whitespace troubleshooting",
    " \tvar  \tx=a +  10\n ",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "x"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_ID, "a"},
        {TOKEN_PLUS, NULL},
        {TOKEN_INT_LITERAL, "10"},
        {TOKEN_LINE_END, NULL}
    },
    7
};

// --- TEST Classic Numbers --- 
LexerTest test4 = {
    "Classic Numbers",
    "   var num = 12 +10.25 \n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "num"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_INT_LITERAL, "12"},
        {TOKEN_PLUS, NULL},
        {TOKEN_FLOAT_LITERAL, "10.25"},
        {TOKEN_LINE_END, NULL}
    },
    7
};

// --- TEST Exponential nums --- 
LexerTest test5 = {
    "Exponential nums",
    "var num = 1.12e5 + 0.55E+2 + 0.58e-4 \n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "num"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_FLOAT_LITERAL, "1.12e5"},
        {TOKEN_PLUS, NULL},
        {TOKEN_FLOAT_LITERAL, "0.55E+2"},
        {TOKEN_PLUS, NULL},
        {TOKEN_FLOAT_LITERAL, "0.58e-4"},
        {TOKEN_LINE_END, NULL}
    },
    9
};

// --- TEST Hex nums --- 
LexerTest test6 = {
    "Hex nums",
    "var num = 0xdd + 0x1F + 0xAA\n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "num"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_HEX_LITERAL, "0xdd"},
        {TOKEN_PLUS, NULL},
        {TOKEN_HEX_LITERAL, "0x1F"},
        {TOKEN_PLUS, NULL},
        {TOKEN_HEX_LITERAL, "0xAA"},
        {TOKEN_LINE_END, NULL}
    },
    9
};

// --- TEST Multiple newlines collapse to single EOL ---
LexerTest test7 = {
    "Multiple newlines collapse to single EOL",
    "\tvar a = 1\n\n\nvar b = 2\n",
    (Token[]) {
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
    },
    10
};

// --- TEST Keyword-like identifiers ---
LexerTest test8 = {
    "Keyword-like identifiers",
    "var var_x = 10\nifclassx1 = 20\n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "var_x"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_INT_LITERAL, "10"},
        {TOKEN_LINE_END, NULL},
        {TOKEN_ID, "ifclassx1"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_INT_LITERAL, "20"},
        {TOKEN_LINE_END, NULL}
    },
    9
};

// --- TEST Function call with parentheses ---
LexerTest test9 = {
    "Function call with parentheses",
    "var x = func(a, b)\n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "x"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_ID, "func"},
        {TOKEN_LEFT_PAREN, NULL},
        {TOKEN_ID, "a"},
        {TOKEN_ID, "b"},
        {TOKEN_RIGHT_PAREN, NULL},
        {TOKEN_LINE_END, NULL}
    },
    9
};

// --- TEST Complex identifiers ---
LexerTest test10 = {
    "Complex identifiers",
    "var _abc = 1\nvar XYZ__123 = 2\n",
    (Token[]) {
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
    },
    10
};

// --- TEST String literals ---
LexerTest test11 = {
    "String literals",
    "var s = \"Ahoj\\n\\\"Sve'te \\\\\\x22\"\n",     // "\\" = "\"        "\x22" = 34 = "
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "s"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_STRING_LITERAL, "Ahoj\n\"Sve'te \\\""},
        {TOKEN_LINE_END, NULL}
    },
    5
};

// --- TEST Empty string and string with \n ---
LexerTest test12 = {
    "Empty string and string with \n",
    "var s = \"\"\nvar space = \"\\n\"\n",
    (Token[]) {
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
    },
    10
};

// --- TEST Arithmetic operators ---
LexerTest test13 = {
    "Arithmetic operators",
    "var x = 10 + 2 - 3 * 4 / 5\n",
    (Token[]) {
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
    },
    13
};

// --- TEST Complex expression with parentheses ---
LexerTest test14 = {
    "Complex expression with parentheses",
    "var result = ((a + b) * (c - d)) / e\n",
    (Token[]) {
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
    },
    19
};

// --- TEST Class ---
LexerTest test15 = {
    "Class keyword and Braces with newlines",
    "class MyClass\n{\n}\n",
    (Token[]) {
        {TOKEN_CLASS, NULL},
        {TOKEN_ID, "MyClass"},
        {TOKEN_LINE_END, NULL},
        {TOKEN_LEFT_BRACE, NULL},
        {TOKEN_LINE_END, NULL},
        {TOKEN_RIGHT_BRACE, NULL},
        {TOKEN_LINE_END, NULL}
    },
    7
};

// --- TEST If ---
LexerTest test16 = {
    "If keyword, IS literal and String, Num token",
    "if (x is String)\n{\n}\nif(s is Num)\n", 
    (Token[]) {
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
        {TOKEN_LINE_END, NULL}
    },
    18
};

// --- TEST Global var ---
LexerTest test17 = {
    "Global var",
    "var __g = 42\n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_GLOBAL_VAR, "__g"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_INT_LITERAL, "42"},
        {TOKEN_LINE_END, NULL}
    },
    5
};

// --- TEST Else keyword ---
LexerTest test18 = {
    "(18) Else keyword",
    "if (x) { } else { }\n",
    (Token[]) {
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
    },
    10
};

// --- TEST Null keyword and literal ---
LexerTest test19 = {
    "Null keyword and literal",
    "var x = null\nif (y is Null) { }\n",
    (Token[]) {
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
    },
    14
};

// --- TEST Return keyword ---
LexerTest test20 = {
    "Return keyword",
    "return foo(only_par,\n only_par)\nreturn x + y\nreturn\n",
    (Token[]) {
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
    },
    14
};

// --- TEST While keyword ---
LexerTest test21 = {
    "While keyword",
    "while (x >\n 0) { x =\n x -\n 1 }\n",
    (Token[]) {
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
    },
    14
};

// --- TEST Import keyword ---
LexerTest test22 = {
    "Import & for keyword",
    "import \"ifj25\" for Ifj\n",
    (Token[]) {
        {TOKEN_IMPORT, NULL},
        {TOKEN_STRING_LITERAL, "ifj25"},
        {TOKEN_FOR, NULL},
        {TOKEN_IFJ, NULL},
        {TOKEN_LINE_END, NULL}
    },
    5
};

// --- TEST Static keyword ---
LexerTest test23 = {
    "Static keyword",
    "static main() { }\nstatic func(\nx){}\n",
    (Token[]) {
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
    },
    16
};

// --- TEST Ifj vstavane funkcie ---
LexerTest test24 = {
    "Ifj vstavane funkcie",
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
    "Ifj.chr()\n",
    (Token[]) {
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
    },
    41
};

// --- TEST Relational operators with numbers ---
LexerTest test25 = {
    "Relational operators with numbers",
    "1 < 2 3.5 > 2.1 10 <= 10 5 >= 5 0 == 0 1 != 0\n",
    (Token[]) {
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
    },
    19
};

// --- TEST Multiline string literal ---
LexerTest test26 = {
    "Multiline string literal",
    "var x = \"\"\"A\nhoj s\\x22\"vete\n\"\"\"\n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "x"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_STRING_LITERAL, "A\nhoj s\\x22\"vete\n"},
        {TOKEN_LINE_END, NULL}
    },
    5
};

// --- TEST Line comment ---
LexerTest test27 = {
    "(27) Line comment",
    "var x = 1 // toto je komentar\nvar y = 2\n",
    (Token[]) {
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
    },
    10
};

// --- TEST Block comment single line ---
LexerTest test28 = {
    "Block comment single line",
    "var x = 1 /* komentar */ var y = 2\n",
    (Token[]) {
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "x"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_INT_LITERAL, "1"},
        {TOKEN_VAR, NULL},
        {TOKEN_ID, "y"},
        {TOKEN_ASSIGN, NULL},
        {TOKEN_INT_LITERAL, "2"},
        {TOKEN_LINE_END, NULL}
    },
    9
};

// --- TEST Block comment multiline ---
LexerTest test29 = {
    "Block comment multiline",
    "var a = 1\n/* komentar\n na viac riadkov */\nvar b = 2\n",
    (Token[]) {
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
    },
    10
};