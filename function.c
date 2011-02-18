#include "function.h"
#include <string.h>

void function_print(Function *f) {
  char * str;
  str = free_toString(f->root);
  ui_print(str);
}


