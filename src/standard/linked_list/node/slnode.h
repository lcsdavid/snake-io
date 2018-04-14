#ifndef SLNODE_H
#define SLNODE_H

#include <assert.h>
#include <stdlib.h>

typedef struct SimplyLinkedNode slnode_t;

typedef struct SimplyLinkedNode {
    slnode_t *next;
    void *data;
} slnode_t;

const slnode_t slnode_default;

slnode_t *slnode_create(slnode_t *next, void *data);

slnode_t *slnode_copy(const slnode_t *slnode);

void slnode_delete(slnode_t *slnode);

#endif
