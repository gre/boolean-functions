#include "btree.h"

/**
 * type : value, variable or operator
 * val :
 *    - if type is value : val is the value
 *    - if type is variable : val is the variable litteral as int value in ascii table. Exemple: x variable is 120 (btw 120=='x')
 *    - if type is operator : the operator enum value
 * left : the left child if exists
 * right : the right child if exists
 */
typedef struct _BoolNode {
  NodeType type;
  int val;
  struct _BoolNode* left;
  struct _BoolNode* right;
} BoolNode;

struct _BoolTree {
  BoolNode* root;
};