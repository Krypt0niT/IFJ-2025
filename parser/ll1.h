#ifndef LL1_H
#define LL1_H

#include "../scanner/token.h"
#include "ast.h" // tvoja definícia ASTNode

// Neterminály
typedef enum {
    NT_PROGRAM,
    NT_STATEMENT,
    NT_EXPRESSION,
    NT_IFSTATEMENT,
    NT_WHILESTATEMENT,
    NT_FORSTATEMENT,
    NT_RETURNSTATEMENT,
    NT_BLOCK,
    NT_ASSIGNMENT,
    NT_VARDECL,
    NT_GLOBALVARDECL,
    NT_FUNCTIONCALL,
    NT_FUNCTIONDECL,
    NT_CLASSDECL,
    NT_IMPORTSTATEMENT,
    NT_COUNT  // počet neterminálov
} NonTerminal;

// Funkcia parsera pre neterminál
typedef ASTNode* (*ParseFunc)(Token** current);

// LL(1) tabuľka
extern ParseFunc ll1_table[NT_COUNT][TOKEN_COUNT];

// Inicializácia tabuľky (naplnenie ukazovateľov)
void initLL1Table(void);

// Funkcia na parsovanie neterminálu podľa tabuľky
ASTNode* parseNonTerminal(NonTerminal nt, Token** current);

#endif
