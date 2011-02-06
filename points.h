#ifndef _POINTS_H
#define _POINTS_H

#include "point.h"

typedef struct _Points Points;

Points* points_init();
void points_free(Points*);

void points_print(Points*); // Must use point_print foreach point

Points* points_parse(char*);
void points_free(Points* set);

int points_contains(Points* set, Point p);

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
 * Remove all points in all into set
 */
int points_removeAll(Points* set, Points* all);

/**
 * Check if :
 * - point doesn't exists
 * - If set contains a point, p is same dimension as this point
 */
int points_add(Points* set, Point p);

int points_remove(Points* set, Point p);

int points_getSize(Points* set);

/**
 * Get an array representation of the Points set. Store the size of element into size
 */
Point* points_toArray(Points* set, int* size);

#endif

