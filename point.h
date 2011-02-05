#ifndef _POINT_H
#define _POINT_H

#include "globals.h"

struct _Point {
  bool* vect;
  int dim;
};

typedef struct _Point Point;

#endif