#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "point.h"
#include "ftree.h"
#include "btree.h"
#include "globals.h"

typedef struct _Function Function;

Function* function_createWithFunctionTree(FunctionTree* tree);

/**
 * Print as expression :
 * print the DNF
 */
void function_print(Function *);

/**
 * Print as Disjunctive Normal Form (DNF)
 */
void function_printAsDNF(Function);

/**
 * Print tree in dot format
 */
void function_printAsTree(Function); // Must use btree_print


void function_setName(Function* f, char* name);

/**
 * Print binary decision diagram (BDD) in dot format
 */
void function_printAsBDD(Function);

void function_printAsTruthTable(Function); // Must use btable_print

void function_printAsKarnaugh(Function); // Must use btable_printKarnaugh

Bool function_eval(Function, Point);

int function_is(Function* f, char* name);

#endif

