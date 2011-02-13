#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "function.h"
#include "points.h"
#include "parser.h"
#include "globals.h"

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

/*
 * return 
    0 :  if everything is ok with the command
    1 :  if the command is to quit
    -1 :  if parse problem
 */
int interp_runCommand(Env* env, char* line);

#endif

