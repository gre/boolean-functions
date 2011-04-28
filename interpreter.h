#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "globals.h"
#include "parser/parser.h"

/**
 * Environement of the interpreter
 */
typedef struct _Env Env;

/**
 * Init the env
 */
extern Env* interp_init();

/**
 * free the env
 */
extern void interp_free(Env*);

/**
 * Run a command into the interpreter.
 * @param instruction : given by the parser
 */
extern void interp_runCommand(Env* env, TPA_Instruction* instruction);

#endif
