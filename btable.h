#ifndef _BTABLE_H
#define _BTABLE_H

#include "globals.h"

struct _TruthTable {
  int size;
  Bool* tab;
};

typedef struct _TruthTable TruthTable;

int btable_equals(TruthTable, TruthTable);

TruthTable btable_parse(char*);
void btable_print(TruthTable);
void btable_printKarnaugh(TruthTable);

#endif

