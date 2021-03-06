#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "ftree.h"
#include "point.h"
#include "btable.h"
#include "btree.h"

struct _TruthTable {
  int size;
  Bool* tab;
};

extern TruthTable* btable_init(int dim) {
  int size;
  for(size=1; size<dim; size*=2);
  TruthTable* table = malloc(sizeof(*table));
  table -> size = size;
  table -> tab = calloc(size, sizeof(Bool)); // alloced and filled with zeros
  return table;
}

extern void btable_free(TruthTable* t) {
  if(t->tab) free(t->tab);
  free(t);
}


extern int btable_getSize(TruthTable* table) {
  return table->size;
}
extern int btable_getDimension(TruthTable* table) {
  int dim = 0, i;
  for(i=1; i<table->size; i*=2) 
    ++dim;
  return dim;
}

extern char* btable_generateVars(TruthTable* table) {
  char* str = calloc(table->size+1, sizeof(*str));
  int i, dim = btable_getDimension(table);
  for(i=0; i<dim; ++i)
    str[i] = 'a'+i;
  str[i] = 0;
  return str;
}

extern void btable_setVal(TruthTable* table, int index, Bool val) {
  table->tab[index] = val;
}

extern Bool btable_getVal(TruthTable* table, int index) {
  return table->tab[index];
}

extern void btable_setPointVal(TruthTable* table, Point p, Bool val) {
  btable_setVal(table, point_toIndex(p), val);
}
extern Bool btable_getPointVal(TruthTable* table, Point p) {
  return btable_getVal(table, point_toIndex(p));
}

extern int btable_equals(TruthTable* a, TruthTable* b) {
  if(a->size != b->size) return 0;
  int i;
  for(i=0; i<a->size; ++i)
    if(a->tab[i] != b->tab[i])
      return 0;
  return 1;
}

extern char* btable_toString(TruthTable* table) {
  if(table==0) return 0;
  int i, c = 0;
  char* out = malloc(sizeof(char)*(table->size+3));
  out[c++] = '(';
  for(i=0; i<table->size; ++i) {
    out[c++] = table->tab[i]==1 ? '1' : '0';
  }
  out[c++] = ')';
  out[c] = '\0';
  return out;
}

extern FunctionTree* btable_toFunctionTree(TruthTable* table, char* vars) {
  FunctionNode *root = 0, *branch, *node;
  Point p;
  int i, j;
  int dim = btable_getDimension(table);
  if(dim==0) return ftree_createWithNode(ftree_newBool(table->tab[0]));
  for(i=0; i<table->size; ++i) {
    if(table->tab[i]) {
      p = point_createWithIndex(i, dim);
      branch = 0;
      for(j=0; j<dim; ++j) {
        node = ftree_newVar(vars[j]);
        if(!p.vect[j])
          node = ftree_newNot(node);
        branch = (branch==0) ? node : ftree_newBin(node, '*', branch);
      }
      root = (root==0) ? branch : ftree_newBin(root, '+', branch);
    }
  }
  if(root==0)
    root = ftree_newBool(0);
  return ftree_createWithNode(root);
}

static BoolNode* rec_btable_toBoolTree(TruthTable* table, int i, char* vars) {
  if(vars[0]==0) return btree_newLeaf(table->tab[i]);
  return btree_newNode(rec_btable_toBoolTree(table, i<<1, vars+1), *vars,
                       rec_btable_toBoolTree(table, i<<1 | 0x1, vars+1));
}

extern BoolTree* btable_toBoolTree(TruthTable* table, char* vars) {
  return btree_createTreeWith(rec_btable_toBoolTree(table, 0, vars));
}

