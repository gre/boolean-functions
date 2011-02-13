#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
#include "parser.h"
#include "utils.h"


struct _Command {
  char* command; // print, expr, table, eval, ...
  char* option; // option like "/e" , ... or 0
  char* output; // file output (for print)
  char* symbol;
  char* op;
  Function* f;
  Points* p;
};


Command* parser_parseCommand(char* str) {
  Command* cmd = malloc(sizeof(*cmd));
  cmd->command = 0;
  cmd->option = 0;
  cmd->output = 0;
  cmd->symbol = 0;
  cmd->op = 0;
  cmd->f = 0;
  cmd->p = 0;
  char *index;
  char* s = str_trim(str);
  str_tolower(s);
  for(index=s; *index && !isspace(*index); ++index); // Move index to next whitespace
  cmd -> command = malloc(sizeof(char) * (index-s+1));
  strncpy(cmd->command, s, index-s);
  
  while(*index && isspace(*index)) ++index; // Move index to next non whitespace
  
  // TODO
  
  return cmd;
}
void parser_freeCommand(Command* cmd) {
  if(cmd->command) free(cmd->command);
  if(cmd->option) free(cmd->option);
  if(cmd->output) free(cmd->output);
  if(cmd->symbol) free(cmd->symbol);
  if(cmd->op) free(cmd->op);
  // TODO : free function for function and poitns
  free(cmd);
}

/**
 * return true if the cmd->command == name
 */
int parser_commandIs(Command* cmd, const char* name) {
  return cmd->command==name || strcmp(cmd->command, name)==0;
}

