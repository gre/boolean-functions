#include "globals.h"
#include "ui.h"
#include "parser/parser.h"

int ui_waitCommand(TPA_Instruction* inst) {
  ui_print("$ ");
  fflush(stdout);
  return pa_parser(inst);
}

void ui_onStart() {
  ui_print("\tBy Gaetan Renaudeau and Nicolae Namolovan\n");
  ui_print("\tBoolean Functions interpeter v%g\n", VERSION);
  ui_print("\tUse --help for more info.\n");
}

void ui_onStop() {
  ui_print("Bye!\n");
}
