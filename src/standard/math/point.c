#include "point.h"

point_t *point_create(double x, double y) {
    point_t *point = calloc(1, sizeof(point_t));
    if (point == (void *) 0) {
        perror("calloc()");
        return (void *) 0;
    }
    *point = (point_t){x, y};
    return point;
}

point_t point_add(point_t A, point_t B) {
    return (point_t){A.x + B.x, A.y + B.y};
}

point_t point_substract(point_t A, point_t B) {
    return (point_t){A.x - B.x, A.y - B.y};
}

double point_distance(point_t A, point_t B) {
    double dx = A.x - B.x;
    double dy = A.y - B.y;
    return sqrt(dx * dx + dy * dy);
}