#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ftree.h"
#include "point.h"
#include "utils.h"
#include "globals.h"

/**
 * type : value, variable or operator
 * val :
 *    - if type is value : val is the value
 *    - if type is variable : val is the variable litteral as int value in ascii table. Exemple: x variable is 120 (btw 120=='x')
 *    - if type is operator : the operator enum value
 * left : the left child if exists
 * right : the right child if exists
 */
struct _FunctionNode {
  NodeType type;
  int val;
  struct _FunctionNode* left;
  struct _FunctionNode* right;
};

struct _FunctionTree {
  FunctionNode* root;
};

FunctionTree* ftree_createWithNode(FunctionNode* node) {
    FunctionTree* tree = malloc(sizeof(*tree));
    tree -> root = node;
    return tree;
}

FunctionNode* ftree_newVar(char s) {
    FunctionNode* node = malloc(sizeof(*node));
    node -> type = NodeType_VARIABLE;
    node -> val = (int)s; 
    node -> left = 0;
    node -> right = 0;
  #ifdef DEBUG
  printf("DEBUG: %p=ftree_newVar(%c)\n", node, s);
  #endif
    return node;
};

FunctionNode* ftree_newBool(int b) {
    FunctionNode* node = malloc(sizeof(*node));
    node -> type = NodeType_VALUE;
    node -> val = (int) b; 
    node -> left = 0;
    node -> right = 0;
  #ifdef DEBUG
  printf("DEBUG: %p=ftree_newBool(%d)\n", node, b);
  #endif
    return node;
};

FunctionNode* ftree_newNot(FunctionNode* node) {
    FunctionNode* n = malloc(sizeof(*n));
    n -> type = NodeType_OPERATOR;
    n -> val = Op_NOT; 
    n -> left = node;
    n -> right = 0;
  #ifdef DEBUG
  printf("DEBUG: %p=ftree_newNot(%p)\n", n, node);
  #endif
    return n;
};

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
  #ifdef DEBUG
  printf("DEBUG: %p=ftree_newBin(%p, %c, %p)\n", node, l, o, r);
  #endif
    return node;

};

// FIXME: it sounds like there is some free() missing
// Should use snprintf everywhere
static char* rec_ftree_toString(FunctionNode* tree) {
  if(tree==0) return "";
  char *sleft, *sright, *sret, op;
  if ( tree -> type == NodeType_OPERATOR) {
    sleft = rec_ftree_toString( tree -> left );
    if(tree->val==Op_NOT) {
      sret = (char*) malloc( sizeof(char) * ( strlen(sleft) + 2 ) );
      op = '!';
      sprintf(sret,"%c%s", op, sleft);
    }
    else {
      sright = rec_ftree_toString( tree -> right );
      sret = (char*) malloc( sizeof(char) * ( strlen(sleft) + strlen(sright) + 4 ) ); // 1 is operator, 2 spaces, \0
      if(tree->val==Op_OR)
        op = '+';
      else if(tree->val==Op_XOR)
        op = '^';
      else
        op = '*';
      sprintf(sret,"(%s%c%s)", sleft, op, sright); 
    }
    return sret;
  }
  
  if ( tree -> type == NodeType_VARIABLE) {
    sret = (char*) malloc(3*sizeof(char));
    snprintf(sret, 2, "%c", (char) tree -> val);
    return sret;
  }
  if ( tree -> type == NodeType_VALUE) {
    sret = (char*) malloc(3*sizeof(char));
    snprintf(sret, 2, "%1d", tree -> val);
    return sret;
  }
  return "";
}

char* ftree_toString(FunctionTree* tree) {
  if(tree==0) return "";
  return rec_ftree_toString(tree->root);
}

static void rec_ftree_getVars(FunctionNode* tree, char* vars) {
  char c;
  if(tree==0) return;
  if(tree->type==NodeType_VARIABLE) {
    c = (char) tree->val;
    if(!util_letterInWord(c, vars))
      vars[strlen(vars)] = c;
  }
  else if(tree->type==NodeType_OPERATOR) {
    rec_ftree_getVars(tree->left, vars);
    rec_ftree_getVars(tree->right, vars);
  }
}

static int charcmp(const void* a, const void* b) {
  return *((char*) a) - *((char*) b);
}

char* ftree_getVars(FunctionTree* ftree) {
  char* vars = calloc(VARIABLE_SIZE+1, sizeof(char)); // max size of variable
  rec_ftree_getVars(ftree->root, vars);
  qsort(vars, strlen(vars), sizeof(*vars), charcmp);
  return vars;
}

static Bool fnode_eval(FunctionNode* node, Point p, char* vars) {
  int i;
  char c;
  Bool l, r;
  if(node==0) return 0;
  if(node->type==NodeType_VALUE) return node->val;
  if(node->type==NodeType_VARIABLE) {
    c = (char) node->val;
    i = util_indexOfLetter(c, vars);
    return p.vect[i];
  }
  if(node->type==NodeType_OPERATOR) {
    l = fnode_eval(node->left, p, vars);
    r = fnode_eval(node->right, p, vars);
    switch(node->val) {
      case Op_OR:
        return l || r;
      case Op_AND:
        return l && r;
      case Op_XOR:
        return (l && !r) || (!l && r);
      case Op_NOT:
        return !l;
    }
  }
  return 0;
}

Bool ftree_eval(FunctionTree* tree, Point p, char* vars) {
  return fnode_eval(tree->root, p, vars);
}

TruthTable* ftree_toTruthTable(FunctionTree* ftree, char* vars) {
  int i, size, len = strlen(vars);
  Point p;
  Bool b;
  TruthTable* table;
  for(i=0, size=1; i<len; ++i)
    size *= 2;
  table = btable_init(size);
  for(i=0; i<size; ++i) {
    p = point_createWithIndex(i, len);
    b = ftree_eval(ftree, p, vars);
    btable_setPointVal(table, p, b);
  }
  return table;
}
