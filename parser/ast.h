typedef enum {
    // --- Literály ---
    AST_INT_LITERAL,
    AST_FLOAT_LITERAL,
    AST_STRING_LITERAL,
    AST_NULL_LITERAL,

    // --- Identifikátory ---
    AST_IDENTIFIER,

    // --- Aritmetické operátory ---
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV,    // /

    // --- Relačné operátory ---
    OP_LT,     // <
    OP_GT,     // >
    OP_LE,     // <=
    OP_GE,     // >=
    OP_EQ,     // ==
    OP_NE,     // !=

    // --- Priradenie a deklarácie ---
    AST_ASSIGNMENT,         // x = expr
    AST_VAR_DECL,           // var x = expr
    AST_GLOBAL_VAR_DECL,    // global x = expr

    // --- Volania a funkcie ---
    AST_FUNCTION_CALL,      // funcName(args)
    AST_FUNCTION_DECL,      // func name(params) { ... }
    AST_RETURN,             // return expr

    // --- Riadiace štruktúry ---
    AST_IF,                 // if (cond) then else
    AST_WHILE,              // while (cond) body
    AST_FOR,                // for (init; cond; step) body

    // --- Triedy a importy ---
    AST_CLASS_DECL,         // class Name { ... }
    AST_IMPORT,             // import something

    // --- Štruktúrne uzly ---
    AST_BLOCK,              // { statement; statement; ... }
    AST_PROGRAM,            // root uzol programu

    // IFJ25
    AST_IFJ_CLASS,
    AST_IFJ_NAME

} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char* value;
    struct ASTNode* child;
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* next;
} ASTNode;