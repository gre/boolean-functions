#ifndef _POINT_H
#define _POINT_H

#include "globals.h"

typedef struct _Point {
  Bool* vect;
  int dim;
} Point;

typedef struct _PointItem {
  Point p;
  struct _PointItem* next;
} PointItem;

/// create and destroy
Point point_init(int dim);
void point_free(Point p);
/**
 * create a point with a dim and a bool array
 */
Point point_create(Bool* vals, int dim);
/**
 * create a point with the index (int) (seen as a binary array)
 */
Point point_createWithIndex(int index, int dim);


/**
 * duplicate a point
 */
Point point_dup(Point src);

/**
 * create a new point by concatenating two points
 */
Point point_concat(Point first, Point second);

/**
 * get the int value of the binary array
 */
int point_toIndex(Point p);

/**
 * Check if two points are equals
 */
int point_equals(Point, Point);

char* point_toString(Point);

/**
 * add a new bool at the beginning of a point
 */
Point point_boolPrepend(Point p, Bool newBool);

#endif


