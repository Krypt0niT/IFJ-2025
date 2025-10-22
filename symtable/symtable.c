#include "symtable.h"
#include <stdint.h>

ifj_SymbolTable ifjsymtable;

/*
ifj_SymTableInit	Inicializácia tabuľky
ifj_SymTableFree	Uvoľnenie celej tabuľky
ifj_Hash	Výpočet hash indexu
ifj_SymbolCreate	Vytvorenie symbolu
ifj_SymbolFree	Uvoľnenie jedného symbolu
ifj_SymTableInsert	Vloženie symbolu
ifj_SymTableSearch	Vyhľadanie symbolu
ifj_SymTableRemove	Odstránenie symbolu
*/

void ifj_SymTableInit(ifj_SymbolTable *table)
{
    if (table == NULL)
        return;

    for (int i = 0; i < IFJ_TABLE_SIZE; i++)
    {
        table->ifjbins[i] = NULL;
    }
}

void ifj_SymTableFree(ifj_SymbolTable *table)
{
    if (table == NULL)
        return;

    for (int i = 0; i < IFJ_TABLE_SIZE; i++)
    {
        ifj_Symbol *current = table->ifjbins[i];

        while (current != NULL)
        {
            ifj_Symbol *next = current->ifjnext;

            if (current->ifjsignature != NULL)
            {
                ifj_FunctionSignature *sig = current->ifjsignature;

                if (sig->ifjparam_names != NULL)
                {
                    for (int j = 0; j < sig->ifjparam_count; j++)
                        free(sig->ifjparam_names[j]);
                    free(sig->ifjparam_names);
                }

                free(sig->ifjname);
                free(sig);
            }

            free(current->ifjname);
            free(current);
            current = next;
        }

        table->ifjbins[i] = NULL;
    }
}


unsigned int ifj_Hash(const char *key)
{
    if (key == NULL)
        return 0;

    unsigned long hash = 5381; // DJB2
    int c;

    while (*key != '\0')
    {
        c = *key;
        key++;
        hash = hash * 33 + c;
    }

    return (unsigned int)(hash % IFJ_TABLE_SIZE);
}


ifj_Symbol *ifj_SymbolCreate(const char *name, ifj_SymbolType type)
{
    if (name == NULL)
        return NULL;

    ifj_Symbol *sym = malloc(sizeof(ifj_Symbol));
    if (sym == NULL)
        return NULL;

    sym->ifjname = malloc(strlen(name) + 1);
    if (sym->ifjname == NULL)
    {
        free(sym);
        return NULL;
    }
    strcpy(sym->ifjname, name);

    sym->ifjtype = type;
    sym->ifjsignature = NULL;
    sym->ifjnext = NULL;

    return sym;
}



void ifj_SymbolFree(ifj_Symbol *sym)
{
    if (sym == NULL)
        return;

    if (sym->ifjsignature != NULL)
    {
        ifj_FunctionSignature *sig = sym->ifjsignature;

        if (sig->ifjparam_names != NULL)
        {
            for (int j = 0; j < sig->ifjparam_count; j++)
                free(sig->ifjparam_names[j]);
            free(sig->ifjparam_names);
        }

        free(sig->ifjname);
        free(sig);
    }

    free(sym->ifjname);
    free(sym);
}


bool ifj_SymTableInsert(ifj_SymbolTable *table, ifj_Symbol *sym)
{
    if (table == NULL || sym == NULL || sym->ifjname == NULL)
        return false;

    unsigned int index = ifj_Hash(sym->ifjname);
    ifj_Symbol *current = table->ifjbins[index];

    while (current != NULL)
    {
        if (strcmp(current->ifjname, sym->ifjname) == 0)
        {
            return false;
        }
        current = current->ifjnext;
    }

    sym->ifjnext = table->ifjbins[index];
    table->ifjbins[index] = sym;

    return true;
}

ifj_Symbol *ifj_SymTableSearch(ifj_SymbolTable *table, const char *name)
{
    if (table == NULL || name == NULL)
        return NULL;

    unsigned int index = ifj_Hash(name);
    ifj_Symbol *current = table->ifjbins[index];

    while (current != NULL)
    {
        if (strcmp(current->ifjname, name) == 0)
            return current;
        current = current->ifjnext;
    }

    return NULL;
}

bool ifj_SymTableRemove(ifj_SymbolTable *table, const char *name)
{
    if (table == NULL || name == NULL)
        return false;

    unsigned int index = ifj_Hash(name);
    ifj_Symbol *current = table->ifjbins[index];
    ifj_Symbol *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->ifjname, name) == 0)
        {
            if (prev == NULL)
                table->ifjbins[index] = current->ifjnext;
            else
                prev->ifjnext = current->ifjnext;

            ifj_SymbolFree(current);
            return true;
        }

        prev = current;
        current = current->ifjnext;
    }

    return false;
}