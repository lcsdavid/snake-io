#ifndef POINT_H
#define POINT_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int x;
	int y;
} point_t;

point_t* point_create(int x, int y);

point_t* point_copy(const point_t *point);

point_t point_add(const point_t *A, const point_t *B);

point_t point_substract(const point_t *A,  const point_t *B);

double point_distance(const point_t *A, const point_t *B);

void point_norm(point_t *point);

#endif