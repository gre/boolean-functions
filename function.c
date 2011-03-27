#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function.h"
#include "ftree.h"
#include "ui.h"

struct _Function {
  FunctionTree* tree; // function tree not simplified
  FunctionTree* fmd; // Disjunctive normal form of the function (simplified)
  BoolTree* btree;
  TruthTable* table;
  char* symbol;
  char* vars; // variables letters in alphabetic order (ex: "abcez")
};

char * sfree;
void function_print(Function *f, FILE* out) {
  fprintf(out, "%s(%s) = %s\n", f->symbol, f->vars, sfree = ftree_toString(f->tree));
  if (sfree != 0) free(sfree);
}
void function_printAsDNF(Function *f, FILE* out) {
  fprintf(out, "%s(%s) = %s\n", f->symbol, f->vars, sfree = ftree_toString(f->fmd));
  if (sfree != 0) free(sfree);
}
void function_printAsTruthTable(Function* f, FILE* out) {
  fprintf(out, "%s(%s) = %s\n", f->symbol, f->vars, sfree = btable_toString(f->table));
  if (sfree != 0) free(sfree);
}

void function_printAsBDD(Function* f, FILE* out) {
  btree_printDot(f->btree, out);
}
void function_printAsTree(Function* f, FILE* out) {
  ftree_printDot(f->fmd, out);
}

void function_printAsKarnaugh(Function* f, FILE* out) {
	//fprintf(out, "%s = %s\n", f->symbol, btable_toStringKarnaugh(f->table,f->vars));
}

static Function* function_init() {
  Function* f = malloc(sizeof(*f));
  f->tree = 0;
  f->fmd = 0;
  f->btree = 0;
  f->table = 0;
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
  f -> tree = tree; // Init tree with the given expr without simplifications
  f -> vars = ftree_getVars(tree);
  f -> table = ftree_toTruthTable(tree, f->vars);
  f -> btree = btree_simplify(btable_toBoolTree(f->table, f->vars));
  f -> fmd = btree_toFunctionTree(f->btree); // Init fmd as the Disjunctive normal form of the function
  return f;
}

Function* function_createWithTruthTable(TruthTable* table) {
  Function* f = function_init();
  f -> table = table;
  f -> vars = btable_generateVars(table);
  f -> tree = btable_toFunctionTree(f->table, f->vars); // Init tree as a basic truth table traduction
  f -> btree = btree_simplify(btable_toBoolTree(f->table, f->vars));
  f -> fmd = btree_toFunctionTree(f->btree); // Init fmd as the Disjunctive normal form of the function
  return f;
}

int function_is(Function* f, char* name) {
  return strcmp(f->symbol, name)==0;
}
