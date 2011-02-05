#ifndef _BTABLE_H
#define _BTABLE_H

#include "globals.h"

struct _TruthTable {
  int size;
  bool* tab;
};

typedef struct _TruthTable TruthTable;

#endif