#ifndef _PARSER_H
#define _PARSER_H

#include "points.h"
#include "function.h"

/**
 * + Global parser functions
 * + All parser utils (Used by function_parse, points_parse , ...) //FIXME: or do we need all parse functions here ?
 */

typedef struct _Command {
  char* command; // print, expr, table, eval, ...
  char* option; // option like "/e" , ... or 0
  char* output; // file output (for print)
  char* symbol;
  char* op;
  Function* f;
  Points* p;
} Command;


Command* parser_parseCommand(char*);
void parser_freeCommand(Command*);

/**
 * return true if the cmd->command == name
 */
int parser_commandIs(Command* cmd, const char* name);

#endif

