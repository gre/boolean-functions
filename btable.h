#ifndef _BTABLE_H
#define _BTABLE_H

/**
 * Represent a Truth table : a big array of boolean containing all possible values of a boolean function
 */
typedef struct _TruthTable TruthTable;

#include "globals.h"
#include "ftree.h"
#include "btree.h"
#include "point.h"

/**
 * Init a truth table with dimension dim
 * Exemple: if dim=3, there is 8 values in the truth table
 */
extern TruthTable* btable_init(int dim);

extern void btable_free(TruthTable* t);

// Getters, setters
extern void btable_setVal(TruthTable* table, int index, Bool val);
extern Bool btable_getVal(TruthTable* table, int index);

extern void btable_setPointVal(TruthTable* table, Point p, Bool val);
extern Bool btable_getPointVal(TruthTable* table, Point p);

extern int btable_getSize(TruthTable* table);
extern int btable_getDimension(TruthTable* table);

/**
 * Generate vars chars with a truth table
 */
extern char* btable_generateVars(TruthTable* table);

/**
 * @return 1 if arguments are equals, 0 else
 */
extern int btable_equals(TruthTable*, TruthTable*);


// Converter to ... functions

extern char* btable_toString(TruthTable*);

/**
 * create a function tree from a truth table
 */
extern FunctionTree* btable_toFunctionTree(TruthTable* table, char* vars);

/**
 * create a bool tree from a truth table (not simplified)
 */
extern BoolTree* btable_toBoolTree(TruthTable* table, char* vars);

#endif

