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
}

FunctionTree* createWithNode(FunctionNode* node) {
    FunctionTree* tree = malloc(sizeof(*tree));
    tree -> root = node;
}

FunctionNode* ftree_newVar(char s) {
    FunctionNode* node = malloc(sizeof(*node));
    node -> type = NodeType_VARIABLE;
    node -> val = (int)s; 
    node -> left = 0;
    node -> right = 0;
    return node;
};

FunctionNode* ftree_newBool(int b) {
    FunctionNode* node = malloc(sizeof(*node));
    node -> type = NodeType_VALUE;
    node -> val = (int) b; 
    node -> left = 0;
    node -> right = 0;
    return node;
};

FunctionNode* ftree_newNot(FunctionNode* node) {
    FunctionNode* node = malloc(sizeof(*node));
    node -> type = NodeType_OPERATOR;
    node -> val = Op_NOT; 
    node -> left = node;
    node -> right = 0;
    return node;
};


char * ftree_toString(FunctionNode* tree) {
  char *sleft, *sright, *sret;
  
  if ( tree -> type == NodeType_OPERATOR) {
    sleft = free_toString( tree -> left );
    sright = free_toString( tree -> right );
    sret = (*char) malloc( sizeof(char) * ( strlen(sleft) + strlen(sright) + 4 ) ); // 1 is operator, 2 spaces, \n
    sprintf(sret,"%s %c %s",sleft,tree->val,sright);
    return sret;
  }
  
  if ( tree -> type == NodeType_VARIABLE) {
    //return (char) 
  }
}

FunctionNode* ftree_newBin(FunctionNode* l, char o, FunctionNode* r) {
    FunctionNode* node = malloc(sizeof(*node));
    node -> type = NodeType_OPERATOR;
    switch(o) {
        case '+': node -> val = Op_OR; break;
        case '*': node -> val = Op_AND; break;
        case '^': node -> val = Op_XOR; break;
    }
    node -> left = l;
    node -> right = r;
    return node;

};

