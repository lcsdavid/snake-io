#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node node_t;

typedef struct node {
    node_t *next;
    void *data;
} node_t;

/* Principal */

node_t *node_create(node_t *next, void *data);

node_t *node_copy(const node_t *node);

void node_delete(node_t *node);

/* Complements */

bool node_empty(const node_t *node);

#endif
