#ifndef _BTABLE_H
#define _BTABLE_H

typedef struct _TruthTable TruthTable;

#include "globals.h"
#include "ftree.h"
#include "btree.h"
#include "point.h"


TruthTable* btable_init(int size);
int btable_getSize(TruthTable* table);
int btable_getDimension(TruthTable* table);
char* btable_generateVars(TruthTable* table);
void btable_setVal(TruthTable* table, int index, Bool val);
Bool btable_getVal(TruthTable* table, int index);

void btable_setPointVal(TruthTable* table, Point p, Bool val);
Bool btable_getPointVal(TruthTable* table, Point p);

int btable_equals(TruthTable*, TruthTable*);

char* btable_toString(TruthTable*);
char* btable_toStringKarnaugh(TruthTable*);
FunctionTree* btable_toFunctionTree(TruthTable* table, char* vars);

BoolTree* btable_toBoolTree(TruthTable* table, char* vars);

#endif

