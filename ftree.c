#include "ftree.h"

/**
 * type : value, variable or operator
 * val :
 *    - if type is value : val is the value
 *    - if type is variable : val is the variable litteral as int value in ascii table. Exemple: x variable is 120 (btw 120=='x')
 *    - if type is operator : the operator enum value
 * left : the left child if exists
 * right : the right child if exists
 */
typedef struct _FunctionNode {
  NodeType type;
  int val;
  struct _FunctionNode* left;
  struct _FunctionNode* right;
} FunctionNode;

struct _FunctionTree {
  FunctionNode* root;
};
