#ifndef _FTREE_H
#define _FTREE_H
/**
 * A F Tree is an arithmetic tree representing the expression 
 * with operators, value and variables
 */

typedef struct _FunctionTree FunctionTree;
typedef struct _FunctionNode FunctionNode;

#include "btable.h"
#include "globals.h"

typedef enum {
  NodeType_VALUE, NodeType_VARIABLE, NodeType_OPERATOR
} NodeType;

typedef enum {
  Op_OR, Op_AND, Op_XOR,
  Op_NOT 
} Operator;

/**
 * create a function tree with a node as root
 */
FunctionTree* ftree_createWithNode(FunctionNode* node);

/**
 * clone a functiontree
 */
FunctionTree* ftree_clone(FunctionTree* node);

/**
 * free a function tree
 */
void ftree_free(FunctionTree*);

void ftree_normalize(FunctionTree*);

TruthTable* ftree_toTruthTable(FunctionTree* ftree, char* vars);

void ftree_printDot(FunctionTree* ftree, FILE* out);

char * ftree_toString(FunctionTree*);

char* ftree_getVars(FunctionTree* ftree);

FunctionNode* ftree_newBin(FunctionNode* l, char o, FunctionNode* r);
FunctionNode* ftree_newNot(FunctionNode* node);
FunctionNode* ftree_newBool(int b);
FunctionNode* ftree_newVar(char s);
FunctionTree* ftree_createWithNode(FunctionNode* node);

#endif

