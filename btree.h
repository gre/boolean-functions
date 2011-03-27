#ifndef _BTREE_H
#define _BTREE_H
/**
 * A BoolTree is a boolean tree representing the truth table
 */

typedef struct _BoolTree BoolTree;
typedef struct _BoolNode BoolNode;

#include "globals.h"
#include "ftree.h"


BoolTree* btree_createTreeWith(BoolNode* root);

BoolNode* btree_newNode(BoolNode* l, char var, BoolNode* r);

BoolNode* btree_newLeaf(int b);

void btree_printDot(BoolTree* btree, FILE* out);

BoolTree* btree_simplify(BoolTree*);

FunctionTree* btree_toFunctionTree(BoolTree* tree);

#endif
