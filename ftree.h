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
extern FunctionTree* ftree_createWithNode(FunctionNode* node);

/**
 * clone a functiontree
 */
extern FunctionTree* ftree_clone(FunctionTree* node);

/**
 * free a function tree
 */
extern void ftree_free(FunctionTree*);

/// Converters
extern TruthTable* ftree_toTruthTable(FunctionTree* ftree, char* vars);
extern char* ftree_toString(FunctionTree*);

/// Printer
extern void ftree_printDot(FunctionTree* ftree, FILE* out);

/**
 * get all vars used in the ftree
 */
extern char* ftree_getVars(FunctionTree* ftree);

/**
 * create nodes
 */
extern FunctionNode* ftree_newBin(FunctionNode* l, char o, FunctionNode* r);
extern FunctionNode* ftree_newNot(FunctionNode* node);
extern FunctionNode* ftree_newBool(int b);
extern FunctionNode* ftree_newVar(char s);
extern FunctionTree* ftree_createWithNode(FunctionNode* node);

#endif

