#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../function/function.h"
#include "../node/node.h"

typedef struct queue {
    node_t *front;
    node_t *back;
} queue_t;

/* Dynamic memory functions */ // Utiles ?

queue_t *queue_create(node_t *front, node_t *back);

void queue_delete(queue_t *queue);


void *queue_front(const queue_t *queue);

void *queue_back(const queue_t *queue);

/* Capacity */

bool queue_empty(const queue_t *queue);

/* Modifiers */

void queue_enqueue(queue_t *queue, void *element);

void queue_dequeue(queue_t *queue);

/* Operations */

void queue_clear(queue_t *queue);

void queue_copy(queue_t *source, queue_t *copy);

void *queue_element_at(queue_t *queue, size_t at);

bool queue_equal(queue_t *first_queue, queue_t *second_queue, bool (*_type_equal_func)(void*, void*));

ssize_t queue_find(queue_t *queue, void *element, bool (*_type_equal_func)(void*, void*));

void queue_insert_at(queue_t *queue, void *element, size_t at);

size_t queue_lenght(queue_t *queue);

#endif
