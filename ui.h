#ifndef _UI_H
#define _UI_H
#include "stdio.h"

#define ui_print printf

char* ui_waitCommand();

void ui_onStart();
void ui_onStop();

#endif

