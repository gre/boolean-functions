#ifndef _BTREE_H
#define _BTREE_H

#include "btable.h"
#include "globals.h"

typedef enum {
  VALUE, VARIABLE, OPERATOR
} NodeType;

typedef enum { // FIXME : don't remember all op required by specs
  OR, AND, XOR,
  NOT // FIXME : using only left child ?
} Operator;

typedef struct _BoolTree BoolTree;


BoolTree* btree_init();
BoolTree* btree_fromExpression(char*);
BoolTree* btree_fromTruthTable(TruthTable);

void btree_free(BoolTree*);

void btree_normalize(BoolTree*);

TruthTable btree_toTruthTable(BoolTree*);

void btree_printDot(BoolTree*);

#endif

