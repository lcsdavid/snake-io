#include "queue.h"

node_t* node_create(void* data, node_t* next, node_t* previous) {
    node_t* node = calloc(1, sizeof(node_t));
    if(node == (void*)0) {
        perror("calloc()");
        return (void*)0;
    }
    node->data = data;
    node->next = next;
    node->previous = previous;
    return node;
}

void node_delete(node_t* node) {
    if(node) {
        free(node->next);
        free(node->previous);
        free(node);
    }
}

queue_t* queue_create() {
    queue_t* queue = calloc(1, sizeof(queue_t));
    if(queue == (void*)0) {
        perror("calloc()");
        return (void*)0;
    }
    queue->size = 0;
    return queue;
}

void queue_delete(queue_t* queue) {
    if(queue) {
        queue_pop_front(queue);
        queue_delete(queue);
        if(queue_empty(queue))
            free(queue);
    }
}

bool queue_empty(const queue_t* queue) {
    return !queue || queue->size < 1;
}

void* queue_front(const queue_t* queue) {
    if(!queue)
        return (void*)0;
    return queue->front->data;
}

void* queue_back(const queue_t* queue) {
    if(!queue)
        return (void*)0;
    return queue->back->data;
}

void queue_push_back(queue_t* queue, void* data) {
    if(queue)
        if(queue_empty(queue))
            queue->front = queue->back = node_create(data, (void*)0, (void*)0);
}

void queue_pop_front(queue_t* queue) {
    if(queue)
        if(!queue_empty(queue)) {
            if(queue->size == 1)
                queue->back = (void*)0;
            else
                queue->front->next->previous = (void*)0;
            free(queue->front);
            queue->front = (void*)0;
        }
}
