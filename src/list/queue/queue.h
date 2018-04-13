#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node node_t;

typedef struct Node {
    node_t* next;
    node_t* previous;
    void* data;
} node_t ;

node_t* node_create(void* data, node_t* next, node_t* previous);

void node_delete(node_t* node);

typedef struct {
    node_t* front;
    node_t* back;
    size_t size;
} queue_t;

queue_t* queue_create();

void queue_delete(queue_t* queue);

bool queue_empty(const queue_t* queue);

void* queue_front(const queue_t* queue);

void* queue_back(const queue_t* queue);

void queue_push_back(queue_t* queue, void* data);

void queue_pop_front(queue_t* queue);

#endif
