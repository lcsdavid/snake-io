#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../node/node.h"

typedef struct Queue {
    node_t *front;
    node_t *back;
} queue_t;

/* Dynamic memory functions */ // Utiles ?
queue_t *queue_create();
void queue_delete(queue_t *queue);

/* Queue primitive functions */
bool queue_is_empty(queue_t queue);

void *queue_front(queue_t queue);

void *queue_back(queue_t queue);

void queue_enqueue(queue_t *queue, void *element);

void queue_dequeue(queue_t *queue);

/* Queue complementary functions */
int queue_lenght(queue_t *queue);

int queue_find(queue_t *queue, void *element);

void *queue_element_at(queue_t *queue, unsigned int at);

void queue_insert_at(queue_t *queue, void* data, unsigned int at);


#endif
