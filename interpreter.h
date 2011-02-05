#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "globals.h"
#include "function.h"
#include "points.h"

struct _Env {
  // ...
  
  // Symbols
  Function* functions;
  int nbfunction;
  
  Points* points;
  int nbpoints;
};

typedef struct _Env Env;

Env* interp_init();
void interp_free(Env*);

int interp_containsSymbol(Env*, char*);

void interp_runCommand(Env*, char*);

void interp_start(Env*);
void interp_stop(Env*);

#endif