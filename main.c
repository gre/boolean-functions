#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "interpreter.h"
#include "ui.h"

int main(int argc, char* argv[]) {
  Env* env = interp_init();
  ui_onStart();
  while(interp_runCommand(env, ui_waitCommand()) != 1);
  ui_onStop();
  interp_free(env);
  return EXIT_SUCCESS;
}
