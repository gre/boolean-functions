#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function.h"
#include "ftree.h"
#include "ui.h"
#include "points.h"
#include "utils.h"

struct _Function {
  FunctionTree* tree; // function tree not simplified
  FunctionTree* fmd; // Disjunctive normal form of the function (simplified)
  BoolTree* btree;
  TruthTable* table;
  char* symbol;
  char* vars; // variables letters in alphabetic order (ex: "abcez")
};


extern void function_print(Function *f, FILE* out) {
  char * sfree;
  fprintf(out, "%s(%s) = %s\n", f->symbol, f->vars, sfree = ftree_toString(f->tree));
  if (sfree != 0) free(sfree);
}
extern void function_printAsDNF(Function *f, FILE* out) {
  char * sfree;
  fprintf(out, "%s(%s) = %s\n", f->symbol, f->vars, sfree = ftree_toString(f->fmd));
  if (sfree != 0) free(sfree);
}
extern void function_printAsTruthTable(Function* f, FILE* out) {
  char * sfree;
  fprintf(out, "%s(%s) = %s\n", f->symbol, f->vars, sfree = btable_toString(f->table));
  if (sfree != 0) free(sfree);
}

extern void function_printEvalPoint(Function* f, Point p, FILE* out) {
  char * sfree;
  fprintf(out, "%s%s = %d\n", f->symbol, sfree = point_toString(p), function_eval(f,p) );
  if (sfree != 0) free(sfree);
}

extern void function_printAsBDD(Function* f, FILE* out) {
  btree_printDot(f->btree, out); 
}
extern void function_printAsTree(Function* f, FILE* out) {
  ftree_printDot(f->fmd, out);
}

extern void function_printAsKarnaugh(Function* f, FILE* out) {
	int rows, cols;
	char * rowsVars, * colsVars;
	Points * colsP, * rowsP;
	PointItem * rowPointItem, * colPointItem;
	rows = function_getVarsLength(f) / 2;
	cols = function_getVarsLength(f) - rows;
	
	rowsVars = calloc(rows+1, sizeof(char));
	colsVars = calloc(cols+1, sizeof(char));
	
	// Variable names
	memcpy(colsVars, f->vars, cols);
	colsVars[cols] = '\0';
	memcpy(rowsVars, &(f->vars[cols]), rows);
	rowsVars[cols] = '\0';
	
	colsP = points_grayCode(cols);
	rowsP = points_grayCode(rows);
	// Column
	fprintf(out, "%-*s%s\n", cols+2, colsVars,
		str_strips(points_toString(colsP),"(),") );
	// Rows
	fprintf(out, "%s\n", rowsVars);
	
	// Rows line by line
	rowPointItem = rowsP->point;
	do {
		// Row value
		fprintf(out, "%-*s", cols+2, str_strips(point_toString(rowPointItem->p),"(),") );
		
		// Columns
		colPointItem = colsP->point;
		do {
			fprintf(out, "%-*d ", cols, function_eval(f, point_concat(colPointItem->p, rowPointItem->p) ) );
			
			colPointItem = colPointItem->next;
		} while (colPointItem != 0);
		
		fprintf(out, "\n");
		
		rowPointItem = rowPointItem->next;
	} while(rowPointItem != 0);
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

extern void function_free(Function* f) {
  if(f->tree != 0) ftree_free(f->tree);
  if(f->fmd != 0) ftree_free(f->fmd);
  if(f->btree != 0) btree_free(f->btree);
  if(f->table != 0) btable_free(f->table);
  if(f->symbol != 0) free(f->symbol);
  if(f->vars != 0) free(f->vars);
}

extern void function_setName(Function* f, char* name) {
  if(f->symbol) free(f->symbol);
  f -> symbol = malloc((1+strlen(name))*sizeof(char));
  strcpy(f->symbol, name);
}

extern Function* function_createWithFunctionTree(FunctionTree* tree) {
  Function* f = function_init();
  f -> tree = tree; // Init tree with the given expr without simplifications
  f -> vars = ftree_getVars(tree);
  f -> table = ftree_toTruthTable(tree, f->vars);
  f -> btree = btree_simplify(btable_toBoolTree(f->table, f->vars));
  f -> fmd = btree_toFunctionTree(f->btree); // Init fmd as the Disjunctive normal form of the function
  return f;
}

extern Function* function_createWithTruthTable(TruthTable* table) {
  Function* f = function_init();
  f -> table = table;
  f -> vars = btable_generateVars(table);
  f -> tree = btable_toFunctionTree(f->table, f->vars); // Init tree as a basic truth table traduction
  f -> btree = btree_simplify(btable_toBoolTree(f->table, f->vars));
  f -> fmd = btree_toFunctionTree(f->btree); // Init fmd as the Disjunctive normal form of the function
  return f;
}

extern Bool function_eval(Function* f, Point p) {
  return btable_getVal(f->table, point_toIndex(p));
}

extern int function_is(Function* f, char* name) {
  return strcmp(f->symbol, name)==0;
}
extern int function_getVarsLength(Function* f) {
	return strlen(f->vars);
}