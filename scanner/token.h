// token.h
#ifndef TOKEN_H
#define TOKEN_H

// Typy tokenov
typedef enum {
    // --- Klucove slova ---
    TOKEN_CLASS,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_IS,
    TOKEN_NULL,
    TOKEN_RETURN,
    TOKEN_VAR,
    TOKEN_WHILE,
    TOKEN_IFJ,
    TOKEN_STATIC,
    TOKEN_IMPORT,
    TOKEN_FOR,
    TOKEN_NUM,
    TOKEN_STRING,
    TOKEN_NULL_LITERAL,

    // --- Identifikator ---
    TOKEN_ID,

    // --- Priradenie ---
    TOKEN_ASSIGN,

    // --- Globalna premenna
    TOKEN_GLOBAL_VAR,

    // --- Literály ---
    TOKEN_INT_LITERAL,
    TOKEN_HEX_LITERAL,
    TOKEN_STRING_LITERAL,
    TOKEN_FLOAT_LITERAL,

    // --- Aritmeticke operatory ---
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,

    // --- Relacne operatory ---
    TOKEN_LT,       // < 
    TOKEN_GT,       // >
    TOKEN_LE,       // <=
    TOKEN_GE,       // >=
    TOKEN_EQ,       // ==
    TOKEN_NE,       // !=

    // --- Zatvorky ---
    TOKEN_LEFT_PAREN,   // (
    TOKEN_RIGHT_PAREN,  // )
    TOKEN_LEFT_BRACE,   // {
    TOKEN_RIGHT_BRACE,  // }

    // --- KOniec riadku ---
    TOKEN_LINE_END,
    
    TOKEN_COUNT, // neplatna hodnota sluzi an urcenie poctu platnych typov

} TokenType;


typedef struct {
    TokenType type;
    char* value; // lexema zo zdroju
} Token;

#endif
