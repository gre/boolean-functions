#ifndef _POINTS_H
#define _POINTS_H

#include "point.h"

struct _PointItem {
  Point p;
  struct _PointItem* next;
};
typedef struct _PointItem PointItem;

/**
 * A Set of points
 */
struct _Points {
  PointEl* points;
};

typedef struct _Points Points;

#endif