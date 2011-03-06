#ifndef _BTABLE_H
#define _BTABLE_H

#include "globals.h"

typedef struct _TruthTable TruthTable;

TruthTable* btable_init(int size);
int btable_getSize(TruthTable* table);
void btable_setVal(TruthTable* table, int index, Bool val);
Bool btable_getVal(TruthTable* table, int index);

int btable_equals(TruthTable*, TruthTable*);

char* btable_toString(TruthTable*);
char* btable_toStringKarnaugh(TruthTable*);

#endif

