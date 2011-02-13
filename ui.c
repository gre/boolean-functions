#include "ui.h"

char buf[LINE_MAX_LENGTH+1];

char* ui_waitCommand() {
  ui_print("$ ");
  scanf("%"LINE_MAX_LENGTH"s", buf);
  return buf;
}

void ui_onStart() {
  ui_print("Boolean Functions interpeter v%g.\n", VERSION);
  ui_print("By Nicolae Namolovan and Gaetan Renaudeau\n");
}

void ui_onStop() {
  ui_print("Bye!\n");
}
