#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "globals.h"
#include "function.h"

struct _Functions {
  Function* functions;
  int size;
};

typedef struct _Functions Functions;

#endif