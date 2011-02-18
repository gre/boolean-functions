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

typedef enum { TPA_UNDEF=0, TPA_VALUE, TPA_VARIABLE, TPA_OPERATOR } TPA_Type;

struct _TPA_Expr {
    int val; // value or num of variable or operator ('+', '*', '^')
    TPA_Type type; // 
    TPA_Expr *left, *right;
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

TPA_Expr* tpa_init() {
    TPA_Expr* t = (TPA_Expr*)malloc(sizeof(*t));
    t -> val = 0;
    t -> type = TPA_UNDEF;
    t -> right = 0;
    t -> left = 0;
    return t;
}

extern TPA_Expr* pa_newBool(int b) { 
    TPA_Expr* t = tpa_init();
    t -> val = b;
    t -> type = TPA_VALUE;
    return t;
}
extern TPA_Expr* pa_newVar(char s) { return (TPA_Expr*) (0x100200 + 0); }
extern TPA_Expr* pa_newCall(char*s, TPA_Expr** t) { return (TPA_Expr*) (0x100300 + 0); }
extern TPA_Expr* pa_newNot(TPA_Expr*e) { return (TPA_Expr*) (0x100400 + 0); }
extern TPA_Expr* pa_newBin(TPA_Expr*l, char o, TPA_Expr*r) { return (TPA_Expr*) (0x100500 + 0); }
extern TPA_Expr* pa_newWildcard() { return (TPA_Expr*) (0x100600 + 2); }
