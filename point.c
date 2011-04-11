#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"
#include "globals.h"

Point point_init(int dim) {
  Point p;
  p.dim = dim;
  p.vect = (Bool*)calloc(dim, sizeof(Bool));
  return p;
}

Point point_dup(Point src) {
	Point p;
	p = point_init(src.dim);
	memcpy(p.vect,src.vect,sizeof(Bool)*src.dim);
	return p;
}

void point_free(Point p) {
	free(p.vect);
}

int point_toIndex(Point p) {
  int index=0, i;
  int pow = 1;
  for(i=0; i<p.dim; ++i) {
    index += p.vect[p.dim-i-1]*pow;
    pow *= 2;
  }
  return index;
}

Point point_create(Bool* vals, int dim) {
  Point p = point_init(dim);
  int i;
  for(i=0; i<dim; ++i)
    p.vect[i] = vals[i];
  return p;
}

Point point_createWithIndex(int index, int dim) {
  Point p = point_init(dim);
  int i;
  for(i=0; i<dim; ++i)
    p.vect[dim-i-1] = (index>>i)&1;
  return p;
}

int point_equals(Point a, Point b) {
  if(a.dim != b.dim) return FALSE;
  int i;
  for(i=0; i<a.dim; ++i)
    if(a.vect[i] != b.vect[i])
      return FALSE;
  return TRUE;
}

char* point_toString(Point p) {
  int i, c = 0;
  char* out = malloc(sizeof(char)*(p.dim*2+3));
  out[c++] = '(';
  for(i=0; i<p.dim; ++i) {
    if(i!=0) out[c++] = ',';
    out[c++] = p.vect[i]==1 ? '1' : '0';
  }
  out[c++] = ')';
  out[c] = '\0';
  return out;
}
