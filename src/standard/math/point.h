#ifndef POINT_H
#define POINT_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	double x;
	double y;
} point_t;

void point_init(point_t *point, double x, double y);

point_t* point_create(double x, double y);

point_t* point_copy(const point_t *point);

point_t point_add(const point_t *A, const point_t *B);

point_t point_substract(const point_t *A,  const point_t *B);

double point_distance(const point_t *A, const point_t *B);

void point_norm(point_t *point);

#endif