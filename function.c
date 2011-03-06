#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function.h"
#include "ftree.h"
#include "ui.h"

struct _Function {
  FunctionTree* tree;
  BoolTree* btree; // the DNF representation of the function : generated on create
  TruthTable* table; // the truth table representation of the function
  char* symbol;
  char* vars; // variables letters in alphabetic order (ex: "abcez")
};

// TODO : print like this : fname(a,b,c) = a+(b*c)
void function_print(Function *f) {
  ui_print("%s = %s\n", f->symbol, ftree_toString(f->tree));
}

void function_printAsTruthTable(Function* f) {
  ui_print("%s = %s\n", f->symbol, btable_toString(f->table));
}

static Function* function_init() {
  Function* f = malloc(sizeof(*f));
  f->symbol = 0;
  f->vars = 0;
  return f;
}

void function_setName(Function* f, char* name) {
  if(f->symbol) free(f->symbol);
  f -> symbol = malloc((1+strlen(name))*sizeof(char));
  strcpy(f->symbol, name);
}

Function* function_createWithFunctionTree(FunctionTree* tree) {
  Function* f = function_init();
  f -> tree = tree;
  f -> vars = ftree_getVars(tree);
  f -> table = ftree_toTruthTable(tree, f -> vars);
  // TODO : generate other types
  return f;
}

Function* function_createWithTruthTable(TruthTable* table) {
  Function* f = function_init();
  f -> table = table;
  // TODO : generate other types
  return f;
}

int function_is(Function* f, char* name) {
  return strcmp(f->symbol, name)==0;
}
