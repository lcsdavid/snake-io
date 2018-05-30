#include "forward_node.h"

void forward_node_init(forward_node_t *forward_node, forward_node_t *next, void *data) {
    assert(forward_node);
    forward_node->next = next;
    forward_node->data = data;
}

forward_node_t *forward_node_create(forward_node_t *next, void *data) {
    forward_node_t *forward_node = calloc(1, sizeof(forward_node_t));
    if(!forward_node) {
        perror("calloc():");
        return NULL;
    }
    forward_node_init(forward_node, next, data);
    return forward_node;
}

forward_node_t *forward_node_copy(const forward_node_t *forward_node);

void forward_node_delete(forward_node_t *forward_node) {
    assert(forward_node);
    free(forward_node->data);
    free(forward_node);
}

/* Complements */

bool forward_node_empty(const forward_node_t *forward_node);

extern const size_t forward_node_size;