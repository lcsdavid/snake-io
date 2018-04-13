#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "../node/dlnode.h"

typedef struct Queue {
    dlnode_t *front;
    dlnode_t *back;
    size_t size;
} queue_t;

const queue_t queue_default = {(void *) 0, (void *) 0, 0};

queue_t *queue_create();

void queue_delete(queue_t *queue);

bool queue_empty(const queue_t *queue);

void *queue_front(const queue_t *queue);

void *queue_back(const queue_t *queue);

void queue_push_back(queue_t *queue, void *data);

void queue_pop_front(queue_t *queue);

#endif
