#include "slnode.h"

slnode_t *slnode_create(slnode_t *next, void *data) {
    slnode_t *slnode = calloc(1, sizeof(slnode_t));
    if (!slnode) {
        perror("calloc()");
        return (void *) 0;
    }
    *slnode = {next, data};
    return slnode;
}

slnode_t *slnode_copy(const slnode_t *slnode) {
    if (!slnode)
        return (void *) 0;
    return slnode_create(slnode_copy(slnode->next), slnode->data);
}

void slnode_delete(slnode_t *slnode);