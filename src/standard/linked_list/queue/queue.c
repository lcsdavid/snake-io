#include "queue.h"

/* Utiles ?
queue_t *queue_create() {
    queue_t *queue = calloc(1, sizeof(queue_t));
    if (queue == (void *) 0) {
        perror("calloc()");
        return (void *) 0;
    }
    *queue = (queue_t) {(void *) 0, (void *) 0, 0};
    return queue;
}

void queue_delete(queue_t *queue) {
    if (queue) {
        queue_pop_front(queue);
        queue_delete(queue);
        if (queue_empty(*queue))
            free(queue);
    }
}

*/

bool queue_is_empty(queue_t queue) {
    return queue.front == NULL || queue.back == NULL;
}

void *queue_front(queue_t queue) {
    return queue.front->data;
}

void *queue_back(queue_t queue) {
    return queue.back->data;
}

void queue_enqueue(queue_t *queue, void *data) {
    assert(queue);
    node_t *node = node_create(NULL, data);
    assert(node);
    if (queue->front == NULL || queue->back == NULL)
        queue->front = node;
    else
        queue->back->next = node;
    queue->back = node;
}

void queue_dequeue(queue_t *queue) {
    assert(queue);
    if (queue->front != NULL && queue->back != NULL) {
        node_t *node = queue->front;
        if(queue->front == queue->back)
            queue->front = queue->back = NULL;
        else
            queue->front = node->next;
        node_delete(node);
    }
}

/* Queue complementary functions */

int queue_lenght_r(queue_t queue, queue_t *save) {
    if(queue_is_empty(queue))
        return 0;
    queue_enqueue(save, queue_front(queue));
    queue_dequeue(&queue);
    return queue_lenght_r(queue, save) + 1;
}

int queue_lenght(queue_t *queue) {
    assert(queue);
    queue_t save = {NULL, NULL};
    int lenght = queue_lenght_r(*queue, &save);
    *queue = save;
    return lenght;
}

int queue_find(queue_t *q, void *data) {
    assert(q);
    queue_t save = {NULL, NULL};
    int index = 0;
    while (queue_front(*q) != data) {
        if(queue_is_empty(*q))
            return -1;
        queue_enqueue(&save, queue_front(*q));
        queue_dequeue(q);
        ++index;
    }
    return index;
}

void *queue_element_at(queue_t *queue, unsigned int at) {
    assert(queue);
    queue_t save = {NULL, NULL};
    void* element = NULL;
    int index = 0;
    while (!queue_is_empty(*queue)) {
        if(index == at)
            element = queue_front(*queue);
        queue_enqueue(&save, queue_front(*queue));
        queue_dequeue(queue);
    }
    *queue = save;
    return element;
}

void queue_insert_at(queue_t *queue, void* element, unsigned int at) {
    assert(queue);
    queue_t save = {NULL, NULL};
    int index = 0;
    while(!queue_is_empty(*queue)) {
        if (index == at)
            queue_enqueue(&save, element);
        queue_enqueue(&save, queue_front(*queue));
        queue_dequeue(queue);
    }
    *queue = save;
}