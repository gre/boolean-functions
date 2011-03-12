#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "point.h"
#include "ftree.h"
#include "btree.h"
#include "globals.h"

typedef struct _Function Function;

Function* function_createWithFunctionTree(FunctionTree* tree);
Function* function_createWithTruthTable(TruthTable* table);

/**
 * Print as expression :
 * print the DNF
 */
void function_print(Function *, FILE* out);

/**
 * Print as Disjunctive Normal Form (DNF)
 */
void function_printAsDNF(Function*, FILE* out);

/**
 * Print tree in dot format
 */
void function_printAsTree(Function*, FILE* out); // Must use btree_print


void function_setName(Function* f, char* name);

/**
 * Print binary decision diagram (BDD) in dot format
 */
void function_printAsBDD(Function*, FILE* out);

void function_printAsTruthTable(Function*, FILE* out); // Must use btable_toString

void function_printAsKarnaugh(Function*, FILE* out); // Must use btable_toStringKarnaugh

Bool function_eval(Function*, Point); // Must use btable_getPointVal

int function_is(Function* f, char* name);

// shortcut to btable_equals
int function_equals(Function*, Function*);

#endif

