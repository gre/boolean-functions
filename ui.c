#include "globals.h"
#include "ui.h"

char buf[1000];

char* ui_waitCommand() {
  ui_print("$ ");
  scanf("%999s", buf);
  return buf;
}

void ui_onStart() {
  ui_print("\tBy Nicolae Namolovan and Gaetan Renaudeau\n");
  ui_print("\tBoolean Functions interpeter v%g\n", VERSION);
  ui_print("type 'help' for more info.\n");
}

void ui_onStop() {
  ui_print("Bye!\n");
}
