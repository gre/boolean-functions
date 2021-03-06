#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "points.h"
#include "point.h"


Points* points_init() {
  Points* p = malloc(sizeof(*p));
  p->symbol = 0;
  p->point = 0;
  return p;
}

static PointItem* points_itemInit(Point point) {
    PointItem* pointItem = malloc(sizeof(*pointItem));
    pointItem->next = 0;
    pointItem->p = point_dup(point);
    return pointItem;
}

void points_setName(Points* p, char* name) {
  if(p->symbol) free(p->symbol);
  p -> symbol = malloc((1+strlen(name))*sizeof(char));
  strcpy(p->symbol, name);
}
int points_is(Points* p, char* name) {
  return strcmp(p->symbol, name)==0;
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

void points_wildOp(Points* points, Point point, char op) {
	int i;
	
    for(i=0; i<point.dim; i++) {
        if (point.vect[i] == -1) { // Verify for wildcard chars
            point = point_dup(point);
            point.vect[i] = 0;
            points_wildOp(points, point, op);
            
            point = point_dup(point);            
            point.vect[i] = 1;
            points_wildOp(points, point, op);
            
            return; // We won't store wild things
        }
    }
	if (op == '+') points_add(points, point);
	else points_remove(points, point);
}

int points_fit(Points* points, Point point) {
	return points_getDim(points) == point.dim;
}

int points_getDim(Points* points) {    
	if (points->point == 0)
		return 0;
	return points->point->p.dim;	
}

void points_add(Points* points, Point point) {
    PointItem* pointItem;
    PointItem* nextPointItem;
    if (points_contains(points,point)) return;
    nextPointItem = points_itemInit(point);
    if (points->point == 0) {
        points->point = nextPointItem;
    } else {
        pointItem = points_getLastPoint(points);
        pointItem->next = nextPointItem;
    }
}

int points_contains(Points* points, Point point) {
	PointItem* pointItem;
	if (points->point == 0) return 0;
  pointItem = points->point;
	do {
		if (point_equals(pointItem->p, point)) return 1;
	} while ( (pointItem = pointItem->next) );
  return 0;
}

void points_remove(Points* points, Point point) {
	PointItem* pointItem, *previousPoint = 0;

    if (!points_contains(points,point)) return;
        
    int size = points_getSize(points);
    
    pointItem = points->point;
	do {
		if (point_equals(pointItem->p, point)) {
			if (previousPoint == 0)
				points->point = (size == 1) ? 0 : pointItem->next;
			else
        previousPoint->next = (pointItem->next != 0) ? pointItem->next : 0;
			break;
		}
		previousPoint = pointItem;
	} while ( (pointItem = pointItem->next) );
    
    return;
}

int points_getSize(Points* set) {
	int size=0;
	PointItem* pointItem;
  if (set->point == 0) return 0;
  size = 1;
	pointItem = set->point;
	while (pointItem->next != 0) {
		pointItem = pointItem->next;
		size++;
	}
	return size;
}

void points_free(Points* set) {
	PointItem* pointItem, *pointItemPrev;
	
    if (set->point == 0) return;
        
	pointItem = set->point;
	while (pointItem->next != 0) {
		point_free(pointItem->p);
		pointItemPrev = pointItem;
		pointItem = pointItem->next;
		free(pointItemPrev);
	}
	set->point = 0;
}

PointItem* points_getLastPoint(Points* points) {
	PointItem *pointItem;
	pointItem = points->point;
	while (pointItem->next != 0)	
		pointItem = pointItem->next;
	return pointItem;
}

Points* points_grayCode(int n) {
	Bool b;
	
	Points* points, * subPoints;
	PointItem* pointItem, *pointItemLast;
	PointItem* mirrorItemFirst, * mirrorItem, * mirrorItemTemp;

	Point point;
	points = points_init();

	if (n == 1) {
		b = 0;
		point.vect = &b;
		point.dim = 1;
		points_add(points,point);

		b = 1;
		point.vect = &b;
		points_add(points,point);

		return points;
	}
	subPoints = points_grayCode(n-1);
	pointItemLast = points_getLastPoint(subPoints);
	
	/**
	 * Algo:
	 * Mirror the points.
	 * Original points vectors prepend with 0, the mirror with 1.
	 */

	mirrorItemFirst = points_itemInit(subPoints->point->p);

	pointItem = subPoints->point;		
	mirrorItem = mirrorItemFirst;

	pointItem->p = point_boolPrepend(pointItem->p, 0);
	mirrorItem->p = point_boolPrepend(mirrorItem->p, 1);

	while (pointItem->next != 0) {
		pointItem = pointItem->next;

	    mirrorItemTemp = points_itemInit(pointItem->p);

	    mirrorItem->next = mirrorItemTemp;
	    
		pointItem->p = point_boolPrepend(pointItem->p, 0);
	    mirrorItemTemp->p = point_boolPrepend(mirrorItemTemp->p, 1);
	    mirrorItem = mirrorItemTemp;
	}
	pointItemLast->next = points_reverse(mirrorItemFirst);
	return subPoints;
}

PointItem * points_reverse(PointItem * p) {
	PointItem * pointItem, * itemPrev = 0, * itemNext;
	
	itemNext = p;
	
	while(itemNext != 0) {
		pointItem = itemNext;
		itemNext = pointItem->next;
		
		pointItem->next = itemPrev;
		itemPrev = pointItem;
	}
	
	return pointItem;
}
