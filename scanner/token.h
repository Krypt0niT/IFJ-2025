// token.h
#ifndef TOKEN_H
#define TOKEN_H

// Typy tokenov
typedef enum {
    // --- Klucove slova ---
    TOKEN_CLASS,// DONE -----------------------
    TOKEN_IF,// DONE -----------------------
    TOKEN_ELSE,// DONE -----------------------
    TOKEN_IS,// DONE -----------------------
    TOKEN_NULL,// DONE -----------------------
    TOKEN_RETURN,// DONE -----------------------
    TOKEN_VAR,// DONE -----------------------
    TOKEN_WHILE,// DONE -----------------------
    TOKEN_IFJ,// DONE -----------------------
    TOKEN_STATIC,// DONE -----------------------
    TOKEN_IMPORT,// DONE -----------------------
    TOKEN_FOR,// DONE -----------------------
    TOKEN_NUM,// DONE -----------------------
    TOKEN_STRING,// DONE -----------------------
    TOKEN_NULL_LITERAL,// DONE -----------------------

    // --- Identifikator ---
    TOKEN_ID,// DONE -----------------------

    // --- Priradenie ---
    TOKEN_ASSIGN, // DONE -----------------------

    // --- Globalna premenna
    TOKEN_GLOBAL_VAR,// DONE -----------------------

    // --- Literály ---
    TOKEN_INT_LITERAL,
    TOKEN_HEX_LITERAL,
    TOKEN_STRING_LITERAL,
    TOKEN_FLOAT_LITERAL,

    // --- Aritmeticke operatory ---
    TOKEN_PLUS,// DONE -----------------------
    TOKEN_MINUS,// DONE -----------------------
    TOKEN_MUL,// DONE -----------------------
    TOKEN_DIV,// DONE -----------------------

    // --- Relacne operatory ---
    TOKEN_LT,       // < DONE -----------------------
    TOKEN_GT,       // > DONE -----------------------
    TOKEN_LE,       // <= DONE -----------------------
    TOKEN_GE,       // >= DONE -----------------------
    TOKEN_EQ,       // == DONE -----------------------
    TOKEN_NE,       // != DONE -----------------------

    // --- Zatvorky ---
    TOKEN_LEFT_PAREN,   // (// DONE -----------------------
    TOKEN_RIGHT_PAREN,  // )// DONE -----------------------
    TOKEN_LEFT_BRACE,   // {// DONE -----------------------
    TOKEN_RIGHT_BRACE,  // }// DONE -----------------------

    // --- KOniec riadku ---
    TOKEN_LINE_END,// DONE -----------------------

} TokenType;


typedef struct {
    TokenType type;
    char* value; // lexema zo zdroju
} Token;

#endif
