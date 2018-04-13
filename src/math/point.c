#include "point.h"

point_t* point_create(double x, double y) {
    point_t* point = calloc(1, sizeof(point_t));
    if(point == (void*)0) {
        perror("calloc()");
        return (void*)0;
    }
    point->x = x;
    point->y = y;
    return point;
}

point_t* point_copy(const point_t* point) {
    if(!point)
        return (void*)0;
    return point_create(point->x, point->y);
}

point_t* point_add(point_t* A, const point_t* B) {
    assert(A && B);
    *A = { A->x + B->x, A->y + B->y };
    return point_copy(A);
}

point_t* point_substract(point_t* A, const point_t* B) {
    assert(A && B);
    *A = { A->x - B->x, A->y - B->y };
    return point_copy(A);
}

double point_distance(const point_t* A, const point_t* B) {
    double dx = A->x - B->x;
    double dy = A->y - B->y;
    return sqrt(dx * dx + dy * dy);
}