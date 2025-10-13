#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define IFJ_TABLE_SIZE 2048

typedef enum {
    IFJ_SYM_VAR,
    IFJ_SYM_FUNC,
    IFJ_SYM_GETTER,
    IFJ_SYM_SETTER
} ifj_SymbolType;

typedef struct ifj_FunctionSignature {
    char *ifjname;
    int ifjparam_count;
    char **ifjparam_names;
} ifj_FunctionSignature;

typedef struct ifj_Symbol {
    char *ifjname;
    ifj_SymbolType ifjtype;
    ifj_FunctionSignature *ifjsignature;
    struct ifj_Symbol *ifjnext;
} ifj_Symbol;

typedef struct {
    ifj_Symbol *ifjbins[IFJ_TABLE_SIZE];
} ifj_SymbolTable;

#endif