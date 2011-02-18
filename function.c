#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function.h"
#include "ftree.h"
#include "ui.h"

void function_print(Function *f) {
  char * str;
  str = ftree_toString(f->tree);
  ui_print("%s", str);
}

static Function* function_init() {
  Function* f = malloc(sizeof(*f));
  return f;
}

Function* function_createWithFunctionTree(FunctionTree* tree) {
  Function* f = function_init();
  f -> tree = tree;
  return f;
}