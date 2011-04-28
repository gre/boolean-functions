#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btable.h"
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
 * right : the right child if exists, unused for NOT node
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

static void fnode_free(FunctionNode* n) {
  if(n==0) return;
  fnode_free(n->left);
  fnode_free(n->right);
  free(n);
}
extern void ftree_free(FunctionTree* tree) {
  fnode_free(tree->root);
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
    FunctionNode* n = malloc(sizeof(*n));
    n -> type = NodeType_OPERATOR;
    n -> val = Op_NOT; 
    n -> left = node;
    n -> right = 0;
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
    return node;

};


static FunctionNode* ftree_cloneNode(FunctionNode* node) {
  if(node==0) return 0;
  FunctionNode* n = malloc(sizeof(*n));
  n->type = node->type;
  n->val = node->val;
  n->left = ftree_cloneNode(node->left);
  n->right = ftree_cloneNode(node->right);
  return n;
}

FunctionTree* ftree_clone(FunctionTree* node) {
  return ftree_createWithNode(ftree_cloneNode(node->root));
}

char ftree_operatorToChar(int val) {
  if(val==Op_OR) return '+';
  if(val==Op_XOR) return '^';
  if(val==Op_AND) return '*';
  return '!';
}

static char* rec_ftree_toString(FunctionNode* tree) {
  char *sleft, *sright, *sret, op;
  if(tree==0) {
    sret = malloc(sizeof(char));
    *sret = 0;
    return sret;
  }
  int size;
  if ( tree -> type == NodeType_OPERATOR) {
    sleft = rec_ftree_toString( tree -> left );
    if(tree->val==Op_NOT) {
      size = strlen(sleft) + 2;
      sret = (char*) malloc( sizeof(char) * size );
      op = '!';
      snprintf(sret,size,"%c%s", op, sleft);
    }
    else {
      sright = rec_ftree_toString( tree -> right );
      size = strlen(sleft) + strlen(sright) + 4; // 1 is operator, 2 spaces, \0
      sret = (char*) malloc( sizeof(char) * size);
      op = ftree_operatorToChar(tree->val);
      snprintf(sret,size,"(%s%c%s)", sleft, op, sright); 
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
  sret = malloc(sizeof(char));
  *sret = 0;
  return sret;
}

char* ftree_toString(FunctionTree* tree) {
  if(tree==0) return 0;
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


/**
 * id = 1 at first call
 */
static void rec_ftree_printDot(FunctionNode* node, FILE* out) {
  if(node==0) return;
  if(node->type==NodeType_VALUE) {
    fprintf(out, "  n%p [label=\"%d\"]\n", node, node->val);
  }
  else if(node->type==NodeType_VARIABLE) {
    fprintf(out, "  n%p [label=\"%c\"]\n", node, (char)node->val);
  }
  else if(node->type==NodeType_OPERATOR) {
    fprintf(out, "  n%p [label=\"%c\"]\n", node, ftree_operatorToChar(node->val));
    fprintf(out, "  n%p -- n%p\n", node, node->left);
    if(node->val != Op_NOT)
      fprintf(out, "  n%p -- n%p\n", node, node->right);
    rec_ftree_printDot(node->left, out);
    rec_ftree_printDot(node->right, out);
  }
}

void ftree_printDot(FunctionTree* ftree, FILE* out) {
  fprintf(out, "## Generated by Boolean Functions v%g\n", VERSION);
  fprintf(out, "graph {\n");
  rec_ftree_printDot(ftree->root, out);
  fprintf(out, "}\n");
}
