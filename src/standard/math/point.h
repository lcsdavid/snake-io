#ifndef POINT_H
#define POINT_H

#include <assert.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	double x;
	double y;
} point_t;

point_t* point_create(double x, double y);

point_t point_add(point_t A, point_t B);

point_t point_substract(point_t A,  point_t B);

double point_distance(point_t B, point_t A);

#endif