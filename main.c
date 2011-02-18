#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "interpreter.h"
#include "ui.h"

int main(int argc, char* argv[]) {
  Env* env = interp_init();
  TPA_Instruction instruction;
  ui_onStart();
  while(ui_waitCommand(&instruction) != -1) {
	 interp_runCommand(env, &instruction); 
  }
  ui_onStop();
  interp_free(env);
  return EXIT_SUCCESS;
}
