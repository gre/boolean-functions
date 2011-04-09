#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "points.h"
#include "point.h"

int points_is(Points* p, char* name) {
  return strcmp(p->symbol, name)==0;
}

void points_setName(Points* p, char* name) {
  if(p->symbol) free(p->symbol);
  p -> symbol = malloc((1+strlen(name))*sizeof(char));
  strcpy(p->symbol, name);
}

Points* points_init() {
  Points* p = malloc(sizeof(*p));
  p->symbol = 0;
  p->point = 0;
  return p;
}

PointItem* points_itemInit(Point point) {
    PointItem* pointItem = malloc(sizeof(*pointItem));
    pointItem->next = 0;
    pointItem->p = point;

    return pointItem;
}

char * points_toString(Points* points) {
    PointItem* pointItem;
    char * out, * pointStr;
    int outLen = 3; // +1 the null terminator, +2 the ", "

    pointItem = points->point;

    out = strdup("");

    if (pointItem == 0) return out;

    do {
        pointStr = point_toString(pointItem->p);

        out = realloc(out, outLen + strlen(pointStr) * sizeof(char));

        if (outLen != 3) {
            strcat(out, ", ");
            outLen+=2;
        }

        strcat(out,pointStr);

        outLen += strlen(pointStr);

        pointItem = pointItem->next;
    } while (pointItem != 0);

    return out;
}

void points_print(Points* points, FILE* out) {
    char * sfree;
    fprintf(out, "{ %s }\n", sfree = points_toString(points));
    if (sfree != 0) free(sfree);
}

void points_add(Points* points, Point point) {
    int i;
    PointItem* pointItem;
    PointItem* nextPointItem;
    Point* newPoint;

    for(i=0; i<point.dim; i++) {
        if (point.vect[i] == -1) { // Verify for wildcard chars

            point.vect[i] = 0;
            points_add(points, point);

            point.vect[i] = 1;
            points_add(points, point);

            return; // We won't store wild things
        }
    }

    nextPointItem = points_itemInit(point);

    if (points->point == 0) {
        points->point = nextPointItem;
    } else {
        pointItem = points->point;
        while (pointItem->next != 0)
            pointItem = pointItem->next;

        pointItem->next = nextPointItem;
    }
}

int points_contains(Points* set, Point p) {
    return 0;
}


void points_remove(Points* set, Point p) {
    if (!points_contains(set,p)) return;
    return;
}
