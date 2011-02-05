#include "points.h"
#include "point.h"

typedef struct _PointItem {
  Point p;
  struct _PointItem* next;
} PointItem;

/**
 * A Set of points
 */
struct _Points {
  PointItem* points;
  char* symbol;
};