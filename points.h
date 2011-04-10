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
int points_contains(Points* set, Point p);

/** Get Points corresponding to this name
* @param char* name
* @return If no Points is found, 0 is returned
**/
Points* points_get(char* name);
int points_is(Points* p, char* name);
void points_setName(Points* p, char* name);

Points* points_parse(char*);
void points_free(Points* set);

char* points_getSymbol(Points*); // Get the name identifier of the points

/**
 * Return the dim of points or 0 if not constraints (no points)
 */
int points_getDim(Points*);

/**
 * Add all points in all into set
 */
int points_addAll(Points* set, Points* all);

/**
 *
 * Check if :
 * - point doesn't exists
 * - If set contains a point, p is same dimension as this point
 */
 void points_add(Points* points, Point point);

/**
 * Remove all points in all into set
 */
int points_removeAll(Points* set, Points* all);

void points_remove(Points* set, Point p);

int points_getSize(Points* set);

/**
 * Get an array representation of the Points set. Store the size of element into size
 */
Point* points_toArray(Points* set, int* size);

#endif

