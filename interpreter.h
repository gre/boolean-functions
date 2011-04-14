#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "function.h"
#include "points.h"
#include "globals.h"
#include "parser/parser.h"

typedef struct _Env Env;

Env* interp_init();
void interp_free(Env*);

int interp_containsSymbol(Env*, char*);

void interp_runCommand(Env* env, TPA_Instruction* instruction);

int interp_pointsOperation(Points* points, char* name, char ope, TPA_Expr** vals);

#endif
