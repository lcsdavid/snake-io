#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Node node_t;

typedef struct Node {
    node_t *next;
    void *data;
} node_t;

node_t *node_create(node_t *next, void *data);

node_t *node_copy(node_t node);

void node_delete(node_t *node);

#endif
