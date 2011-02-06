#ifndef _POINT_H
#define _POINT_H

#include "globals.h"

typedef struct _Point {
  Bool* vect;
  int dim;
} Point;

Point point_create(Bool*, int);

int point_equals(Point, Point);

void point_print(Point);

#endif


