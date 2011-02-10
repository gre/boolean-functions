#ifndef _FTREE_H
#define _FTREE_H
/**
 * A F Tree is a function tree representing the expression 
 * with operators, value and variables
 */

#include "btable.h"
#include "globals.h"

typedef enum {
  VALUE, VARIABLE, OPERATOR
} NodeType;

typedef enum { // FIXME : don't remember all op required by specs
  OR, AND, XOR,
  NOT // FIXME : using only left child ?
} Operator;

typedef struct _FunctionTree FunctionTree;


FunctionTree* ftree_init();
FunctionTree* ftree_fromExpression(char*);
FunctionTree* ftree_fromTruthTable(TruthTable);

void ftree_free(FunctionTree*);

void ftree_normalize(FunctionTree*);

TruthTable ftree_toTruthTable(FunctionTree*);

void ftree_printDot(FunctionTree*);

#endif

