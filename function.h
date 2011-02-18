#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "point.h"
#include "ftree.h"
#include "btree.h"
#include "globals.h"

struct _Function {
  FunctionTree* tree;
  BoolTree* btree; // the DNF representation of the function : generated on create
  TruthTable* table; // the truth table representation of the function
  char* expr; // Origin expression if Function has been defined as expression, generated else
  char* symbol;
};

typedef struct _Function Function;

Function* function_init(); // useless ?

/**
 * Find the format (table? expr?) and init the function
 * generate all fields
 */
Function* function_parse(char*); 

/**
 * Print as expression :
 * if function has been defined as expression: print it,
 * else, print the DNF
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

/**
 * Print binary decision diagram (BDD) in dot format
 */
void function_printAsBDD(Function);

void function_printAsTruthTable(Function); // Must use btable_print

void function_printAsKarnaugh(Function); // Must use btable_printKarnaugh

Bool function_eval(Function, Point);


#endif

