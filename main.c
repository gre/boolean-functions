#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "interpreter.h"
#include "ui.h"

void showHelp(char* argv0) {
  printf("Usage: %s\n", argv0);
  printf("This program is a boolean functions interpeter. Here is the synthax :\n");
  printf("\n");
  printf("Create funct function with logic expression.\n");
  printf("\texpr funct = (x*y)+!a\n");
  printf("\n");
  printf("Create funct function with truth table.\n");
  printf("\ttable funct = (0,1,0,1)\n");
  printf("\n");
  printf("Print funct as logic expression.\n");
  printf("\tprint funct /e [fichier]\n");
  printf("\n");
// TODO ...
}

int main(int argc, char* argv[]) {
  if(argc==2) {
    if(strcmp(argv[1], "--help")==0) {
      showHelp(argv[0]);
      return EXIT_SUCCESS;
    }
  }
  
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
