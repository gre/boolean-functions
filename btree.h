#ifndef _BTREE_H
#define _BTREE_H

/**
 * A BoolTree is a boolean tree representing a function.
 * each node is a BoolNode
 * each leaf is a value for correspondant path (from root)
 *  Exemple: a->b->c->1 means : a*b*c = 1
 */
typedef struct _BoolTree BoolTree;
typedef struct _BoolNode BoolNode;

#include "globals.h"
#include "ftree.h"

/**
 * Create a bool tree with a node as root
 */
extern BoolTree* btree_createTreeWith(BoolNode* root);

/**
 * Create a new node for variable var with left and right childs
 */
extern BoolNode* btree_newNode(BoolNode* l, char var, BoolNode* r);

extern void btree_free(BoolTree* tree);

/**
 * Create a new leaf with value b
 */
extern BoolNode* btree_newLeaf(int b);

/**
 * Are two btree equals ?
 */
extern int btree_equals(BoolNode* a, BoolNode* b);

/**
 * Print a btree as Dot format into out
 */
extern void btree_printDot(BoolTree* btree, FILE* out);

/**
 * Simplify a BoolTree as BDD
 */
extern BoolTree* btree_simplify(BoolTree*);

/// Converters

/**
 * create a function tree with a btree
 */
extern FunctionTree* btree_toFunctionTree(BoolTree* tree);

#endif
