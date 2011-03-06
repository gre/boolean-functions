#ifndef _BTABLE_H
#define _BTABLE_H

typedef struct _TruthTable TruthTable;

#include "globals.h"
#include "ftree.h"


TruthTable* btable_init(int size);
int btable_getSize(TruthTable* table);
int btable_getDimension(TruthTable* table);
char* btable_generateVars(TruthTable* table);
void btable_setVal(TruthTable* table, int index, Bool val);
Bool btable_getVal(TruthTable* table, int index);

int btable_equals(TruthTable*, TruthTable*);

char* btable_toString(TruthTable*);
char* btable_toStringKarnaugh(TruthTable*);
FunctionTree* btable_toFunctionTree(TruthTable* table, char* vars);

#endif

