#include "stdlib.h"
#include "interpreter.h"
#include "parser/parser.h"

struct _Env {
  // ...
  
  // Symbols
  Function* functions;
  int nbfunction;
  
  Points* points;
  int nbpoints;
};

Env* interp_init() {
  Env* env = malloc(sizeof(*env));
  return env;
}
void interp_free(Env* env) {
  free(env);
}

void interp_runCommand(Env* env, TPA_Instruction* instruction) {
	// TODO
}

extern TPA_Expr* pa_newBool(int b)                         { return (TPA_Expr*) (0x100100 + b); }
extern TPA_Expr* pa_newVar(char s)                         { return (TPA_Expr*) (0x100200 + 0); }
extern TPA_Expr* pa_newCall(char*s, TPA_Expr** t)          { return (TPA_Expr*) (0x100300 + 0); }
extern TPA_Expr* pa_newNot(TPA_Expr*e)                     { return (TPA_Expr*) (0x100400 + 0); }
extern TPA_Expr* pa_newBin(TPA_Expr*l, char o, TPA_Expr*r) { return (TPA_Expr*) (0x100500 + 0); }
extern TPA_Expr* pa_newWildcard()                          { return (TPA_Expr*) (0x100600 + 2); }
