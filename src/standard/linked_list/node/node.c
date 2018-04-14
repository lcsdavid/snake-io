#include "node.h"

node_t *node_create(node_t *next, void *data) {
    node_t *node = calloc(1, sizeof(node_t));
    if (!node) {
        perror("calloc()");
        return NULL;
    }
    *node = {next, data};
    return node;
}

node_t *node_copy(node_t node) {
    return node_create(NULL, node.data);
}

void node_delete(node_t *node) {
    free(node->data);
    free(node);
}