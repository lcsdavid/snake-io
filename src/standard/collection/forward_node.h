#ifndef FORWARD_NODE_H
#define FORWARD_NODE_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct forward_node forward_node_t;

typedef struct forward_node {
    forward_node_t *next;
    void *data;
} forward_node_t;

/* Principal */

forward_node_t *forward_node_create(forward_node_t *next, void *data);

forward_node_t *forward_node_copy(const forward_node_t *forward_node);

void forward_node_delete(forward_node_t *forward_node);

/* Complements */

bool forward_node_empty(const forward_node_t *forward_node);

extern const size_t forward_node_size;

#endif
