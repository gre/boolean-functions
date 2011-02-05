#ifndef _BTREE_H
#define _BTREE_H

#include "globals.h"

typedef enum {
  VALUE, VARIABLE, OPERATOR
} NodeType;

typedef enum { // FIXME : don't remember all op required by specs
  OR, AND, XOR,
  NOT // FIXME : using only left child ?
} Operator;

/**
 * type : value, variable or operator
 * val :
 *    - if type is value : val is the value
 *    - if type is variable : val is the variable litteral as int value in ascii table. Exemple: x variable is 120 (btw 120=='x')
 *    - if type is operator : the operator enum value
 * left : the left child if exists
 * right : the right child if exists
 */
struct _BoolNode {
  NodeType type;
  int val;
  struct _BoolNode* left;
  struct _BoolNode* right;
};

typedef struct _BoolNode BoolNode;

struct _BoolTree {
  BoolNode* root;
};

typedef struct _BoolTree BoolTree;

#endif