#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct node node_t;

typedef struct node {
    node_t *next;
    void *data;
} node_t;

/* Principal */

node_t *node_create(node_t *next, void *data);

void node_delete(node_t *node);

/* Complements */

node_t *node_copy(node_t node);

int8_t node_is_empty(node_t node);

#endif
