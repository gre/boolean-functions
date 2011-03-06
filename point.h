#ifndef _POINT_H
#define _POINT_H

#include "globals.h"

typedef struct _Point {
  Bool* vect;
  int dim;
} Point;

Point point_create(Bool* vals, int dim);
Point point_createWithIndex(int index, int dim);
int point_toIndex(Point p);

int point_equals(Point, Point);

char* point_toString(Point);

#endif


