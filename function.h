#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "globals.h"
#include "btree.h"

struct _Function {
  BoolTree* tree; // Or else a btable representation , maybe both generated when created
  char* symbol;
};

typedef struct _Function Function;

#endif