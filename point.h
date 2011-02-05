#ifndef _POINTS_H
#define _POINTS_H

#include "globals.h"

typedef struct _Point {
  bool* vect;
  int dim;
} Point;

Point point_create(bool*, int);

int point_equals(Point, Point);

void point_print(Point);

#endif