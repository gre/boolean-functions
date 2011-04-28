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
  printf("Print the truth table for the function funct.\n");
  printf("\tprint funct /t [fichier]\n");
  printf("\n");
  printf("The function funct in dot format.\n");
  printf("\tprint funct /a [fichier]\n");
  printf("\n");
  printf("The bdd of the function funct in dot format.\n");
  printf("\tprint funct /b [fichier]\n");
  printf("\n");
  printf("The karnaugh table for function funct.\n");
  printf("\tprint funct /k [fichier]\n");
  printf("\n\n");
  printf("Operations on points:\n");
  printf("\tCreate: point pid = (*0)\n");
  printf("\tAdd: point pid += (01)\n");
  printf("\tDelete: point pid -= (01)\n");
  printf("\n\n");
  printf("Evaluate a function with a set of points.\n");
  printf("\teval funct pid\n");  
  printf("\n");
  printf("Evaluate a function with a point (01).\n");
  printf("\teval funct (01)\n");
  printf("\n");
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
	int status = 0;
  while(status != -1) {
		status = ui_waitCommand(&instruction);
		if(status==1)
			interp_runCommand(env, &instruction); 
  }
  ui_onStop();
  interp_free(env);
  return EXIT_SUCCESS;
}
