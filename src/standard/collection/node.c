#include "node.h"

/* Principal */

const size_t node_size = sizeof(node_t);

void node_init(node_t *node, node_t *previous, node_t *next, void *data) {
    assert(node);
    node->previous = previous;
    node->next = next;
    node->data = data;
}

node_t *node_create(node_t *previous, node_t *next, void *data) {
    node_t *node = calloc(1, sizeof(node_t));
    if(!node) {
        perror("calloc():");
        return NULL;
    }
    node_init(node, previous, next, data);
    return node;
}

node_t *node_copy(const node_t *node) {
    assert(node);
    return node_create(NULL, NULL, node->data);
}

void node_delete(node_t *node) {
    assert(node);
    free(node->data);
    free(node);
}

/* Complements */

bool node_empty(const node_t *node) {
    assert(node);
    return node->data == NULL;
}

