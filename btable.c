#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "btable.h"

struct _TruthTable {
  int size;
  Bool* tab;
};

TruthTable* btable_init(int size) {
  int i;
  for(i=1; i<size; i*=2);
  if(i==1)
    size = 0;
  else
    size = i;
	#ifdef DEBUG
	printf("DEBUG: size: %d\n", size);
	#endif
  TruthTable* table = malloc(sizeof(*table));
  table -> size = size;
  table -> tab = calloc(size, sizeof(Bool)); // alloced and filled with zeros
  return table;
}

int btable_getSize(TruthTable* table) {
  return table->size;
}

void btable_setVal(TruthTable* table, int index, Bool val) {
  table->tab[index] = val;
}

Bool btable_getVal(TruthTable* table, int index) {
  return table->tab[index];
}

int btable_equals(TruthTable* a, TruthTable* b) {
  if(a->size != b->size) return 0;
  int i;
  for(i=0; i<a->size; ++i)
    if(a->tab[i] != b->tab[i])
      return 0;
  return 1;
}

char* btable_toString(TruthTable* table) {
  if(table==0) return "";
  int i, c = 0;
  char* out = malloc(sizeof(char)*(table->size*2+3));
  out[c++] = '(';
  for(i=0; i<table->size; ++i) {
    if(i!=0) out[c++] = ',';
    out[c++] = table->tab[i]==1 ? '1' : '0';
  }
  out[c++] = ')';
  out[c] = '\0';
  return out;
}
char* btable_toStringKarnaugh(TruthTable* table) {
  return 0;
}

