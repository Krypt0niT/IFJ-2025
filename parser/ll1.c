#include "ll1.h"
#include <stdio.h>
#include <stdlib.h>

// Deklarácie funkcií parsera pre konkrétne neterminály
ASTNode* parseProgram(Token** current);
ASTNode* parseStatement(Token** current);
ASTNode* parseExpression(Token** current);
ASTNode* parseIfStatement(Token** current);
// … ďalej podľa neterminálov

// Definícia tabuľky
ParseFunc ll1_table[NT_COUNT][TOKEN_COUNT] = { NULL };

// Naplnenie tabuľky ukazovateľmi na funkcie
void initLL1Table(void) {
    ll1_table[NT_PROGRAM][TOKEN_ID] = parseStatement;
    ll1_table[NT_PROGRAM][TOKEN_VAR]      = parseStatement;
    ll1_table[NT_PROGRAM][TOKEN_IF]       = parseStatement;
    ll1_table[NT_PROGRAM][TOKEN_LEFT_BRACE] = parseStatement;

    ll1_table[NT_STATEMENT][TOKEN_IF]    = parseIfStatement;
    ll1_table[NT_STATEMENT][TOKEN_VAR]   = parseStatement;       // napr. parseVarDecl
    ll1_table[NT_STATEMENT][TOKEN_ID] = parseStatement;    // napr. parseAssignment

    ll1_table[NT_EXPRESSION][TOKEN_ID] = parseExpression;
    // ... ďalej doplniť podľa gramatiky
}

// Parsovanie neterminálu podľa tabuľky
ASTNode* parseNonTerminal(NonTerminal nt, Token** current) {
    Token t = (*current)->type; // predpokladáme, že token type = Terminal
    ParseFunc func = ll1_table[nt][t];
    if (!func) {
        fprintf(stderr, "Syntax error: unexpected token %d for nonterminal %d\n", t, nt);
        return NULL;
    }
    return func(current);
}
