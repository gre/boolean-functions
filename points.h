#ifndef _POINTS_H
#define _POINTS_H

#include "point.h"
#include "parser/parser.h"
#include "globals.h"

/**
 * A Set of points
 */
struct _Points {
  PointItem* point; // Very first point
  char* symbol;
};

typedef struct _Points Points;

Points* points_init();
void points_free(Points*);

char * points_toString(Points*); // Must use point_print foreach point
void points_print(Points* points, FILE* out);
int points_contains(Points* points, Point point);

int points_is(Points* p, char* name);
void points_setName(Points* p, char* name);

void points_free(Points* set);

/**
 * Return the dim of points or 0 if not constraints (no points)
 */
int points_getDim(Points*);

/**
 * Will expend *
 * If op == + it  will call points_add else points_remove
 */
void points_wildOp(Points* points, Point point, char op);

/**
 *
 * Check if :
 * - point doesn't exists
 * - If set contains a point, p is same dimension as this point
 */
void points_add(Points* points, Point point);

void points_remove(Points* points, Point point);

int points_getSize(Points* set);

/**
 * Check if point fit the points (have the size of the points)
 */
int points_fit(Points* points, Point point);
int points_pointDim(Points* points);

Points* points_grayCode(int n);
PointItem* points_getLastPoint(Points* points);
PointItem * points_reverse(PointItem * p);

#endif
