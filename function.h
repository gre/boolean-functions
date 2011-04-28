#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "point.h"
#include "ftree.h"
#include "btree.h"
#include "globals.h"

/**
 * A function contains all representations of a function
 */
typedef struct _Function Function;

/**
 * Create a function with a function tree
 */
extern Function* function_createWithFunctionTree(FunctionTree* tree);

/**
 * Create a function with a truth table
 */
extern Function* function_createWithTruthTable(TruthTable* table);

/**
 * free a function
 */
extern void function_free(Function* f);

/**
 * Print as expression :
 * print the DNF
 */
extern void function_print(Function *, FILE* out);

/**
 * Print as Disjunctive Normal Form (DNF)
 */
extern void function_printAsDNF(Function*, FILE* out);

/**
 * Print tree in dot format
 */
extern void function_printAsTree(Function*, FILE* out); // Must use btree_print


extern void function_setName(Function* f, char* name);

/**
 * Print binary decision diagram (BDD) in dot format
 */
extern void function_printAsBDD(Function*, FILE* out);

extern void function_printAsTruthTable(Function*, FILE* out); // Must use btable_toString

extern void function_printAsKarnaugh(Function*, FILE* out); // Must use btable_toStringKarnaugh

extern void function_printEvalPoint(Function* f, Point p, FILE* out);

extern Bool function_eval(Function*, Point); // Must use btable_getPointVal

extern int function_is(Function* f, char* name);

// shortcut to btable_equals
extern int function_equals(Function*, Function*);

extern int function_getVarsLength(Function* f);

#endif

