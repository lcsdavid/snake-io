#include "point.h"

point_t *point_create(int x, int y) {
    point_t *point = calloc(1, sizeof(point_t));
    if (point == (void *) 0) {
        perror("calloc()");
        return (void *) 0;
    }
    *point = (point_t){x, y};
    return point;
}

point_t point_add(const point_t *A, const point_t *B) {
    assert(A && B);
    return (point_t){A->x + B->x, A->y + B->y};
}

point_t point_substract(const point_t *A, const point_t *B) {
    assert(A && B);
    return (point_t){A->x - B->x, A->y - B->y};
}

double point_distance(const point_t *A, const point_t *B) {
    assert(A && B);
    point_t point = point_substract(A, B);
    return sqrt(point.x * point.x + point.y * point.y);
}

void point_norm(point_t *point) {
    assert(point);
    double d = sqrt(point->x * point->x + point->y * point->y);
    point->x /= d;
    point->y /= d;
}