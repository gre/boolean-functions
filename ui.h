#ifndef _UI_H
#define _UI_H
#include "stdio.h"
#include "parser/parser.h"

#define ui_print printf

int ui_waitCommand(TPA_Instruction* inst);

void ui_onStart();
void ui_onStop();

#endif

