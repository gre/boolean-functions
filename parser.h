#ifndef _PARSER_H
#define _PARSER_H

#include "points.h"
#include "function.h"

/**
 * + Global parser functions
 * + function_parse, points_parse,.. //FIXME: or do we need all parse functions here ?
 */


typedef struct _Command Command;

Command* parser_parseCommand(char*);
void parser_freeCommand(Command*);

/**
 * return true if the cmd->command == name
 */
int parser_commandIs(Command* cmd, const char* name);

#endif

