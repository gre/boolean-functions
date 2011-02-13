#include "stdlib.h"
#include "interpreter.h"

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

int interp_runCommand(Env* env, char* line) {
  return 0;
}
