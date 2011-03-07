#ifndef _FTREE_H
#define _FTREE_H
/**
 * A F Tree is a function tree representing the expression 
 * with operators, value and variables
 */

typedef struct _FunctionTree FunctionTree;
typedef struct _FunctionNode FunctionNode;

#include "btable.h"
#include "globals.h"

typedef enum {
  NodeType_VALUE, NodeType_VARIABLE, NodeType_OPERATOR
} NodeType;

typedef enum { // FIXME : don't remember all op required by specs
  Op_OR, Op_AND, Op_XOR,
  Op_NOT 
} Operator;


FunctionTree* ftree_createWithNode(FunctionNode* node);

FunctionTree* ftree_clone(FunctionTree* node);

FunctionTree* ftree_fromExpression(char*);

void ftree_free(FunctionTree*);

void ftree_normalize(FunctionTree*);

TruthTable* ftree_toTruthTable(FunctionTree* ftree, char* vars);

void ftree_printDot(FunctionTree*);

char * ftree_toString(FunctionTree*);

char* ftree_getVars(FunctionTree* ftree);

FunctionNode* ftree_newBin(FunctionNode* l, char o, FunctionNode* r);
FunctionNode* ftree_newNot(FunctionNode* node);
FunctionNode* ftree_newBool(int b);
FunctionNode* ftree_newVar(char s);
FunctionTree* ftree_createWithNode(FunctionNode* node);


FunctionTree* ftree_simplify(FunctionTree* ftree);
#endif

