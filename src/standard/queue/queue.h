#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "../function/function.h"
#include "../node/node.h"

typedef struct queue {
    node_t *front;
    node_t *back;
} queue_t;

/* Dynamic memory functions */ // Utiles ?

queue_t *queue_create(node_t *front, node_t *back);

void queue_delete(queue_t *queue);

/* Queue primitive functions */

void *queue_front(queue_t queue);

void *queue_back(queue_t queue);

void queue_enqueue(queue_t *queue, void *element);

void queue_dequeue(queue_t *queue);

int8_t queue_is_empty(queue_t queue);

/* Queue complementary functions */

void queue_copy(queue_t *source, queue_t *copy);

void *queue_element_at(queue_t *queue, unsigned int at);

void queue_empty(queue_t *queue);

int queue_find(queue_t *queue, void *element, int8_t (*comparison_func)(void*, void*));

void queue_insert_at(queue_t *queue, void *element, unsigned int at);

int8_t queue_is_equal(queue_t *first_queue, queue_t *second_queue, int8_t (*comparison_func)(void*, void*));

unsigned int queue_lenght(queue_t *queue);

#endif
