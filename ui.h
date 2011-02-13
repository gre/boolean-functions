#ifndef _UI_H
#define _UI_H

#define LINE_MAX_LENGTH 1000

#define ui_print printf

char* ui_waitCommand();

void ui_onStart();
void ui_onStop();

#endif

