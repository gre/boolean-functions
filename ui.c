#include "globals.h"
#include "ui.h"
#include "parser/parser.h"

int ui_waitCommand(TPA_Instruction* inst) {
  ui_print("$ ");
  fflush(stdout);
  return pa_parser(inst);
}

void ui_onStart() {
  ui_print("\tBy Nicolae Namolovan and Gaetan Renaudeau\n");
  ui_print("\tBoolean Functions interpeter v%g\n", VERSION);
  ui_print("type 'help' for more info.\n");
}

void ui_onStop() {
  ui_print("Bye!\n");
}
