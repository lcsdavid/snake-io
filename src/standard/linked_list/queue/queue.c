#include "queue.h"

/* Dynamic memory functions */

queue_t *queue_create(node_t *front, node_t *back) {
    queue_t *queue = calloc(1, sizeof(queue_t));
    if (!queue) {
        perror("calloc()");
        return NULL;
    }
    *queue = (queue_t) {front, back};
    return queue;
}

void queue_delete(queue_t *queue) {
    if (queue) {
        queue_empty(queue);
        free(queue);
    }
}

/* Queue primitive functions */

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
        if (queue->front == queue->back)
            queue->front = queue->back = NULL;
        else
            queue->front = node->next;
        node_delete(node);
    }
}

bool queue_is_empty(queue_t queue) {
    return queue.front == NULL || queue.back == NULL;
}

/* Queue complementary functions */

void queue_copy(queue_t *source, queue_t *copy) {
    assert(source && copy);
    queue_t save = {NULL, NULL};
    while (!queue_is_empty(*source)) {
        queue_enqueue(&save, queue_front(*source));
        queue_enqueue(copy, queue_front(*source));
        queue_dequeue(source);
    }
    while (!queue_is_empty(save)) {
        queue_enqueue(source, queue_front(save));
        queue_dequeue(&save);
    }
}

void *queue_element_at(queue_t *queue, unsigned int at) {
    assert(queue);
    queue_t save = {NULL, NULL};
    void *element = NULL;
    int index = 0;
    while (!queue_is_empty(*queue)) {
        if (index == at)
            element = queue_front(*queue);
        queue_enqueue(&save, queue_front(*queue));
        queue_dequeue(queue);
    }
    *queue = save;
    return element;
}

void queue_empty(queue_t *queue) {
    assert(queue);
    while (!queue_is_empty(*queue)) {
        queue_dequeue(queue);
    }
}

int queue_find(queue_t *q, void *element, bool (*comparison_func)(void*, void*)) {
    assert(q);
    if(comparison_func == NULL)
        comparison_func = &generic_ptr_is_equal;
    queue_t save = {NULL, NULL};
    int index = 0;
    while (comparison_func(queue_front(*q), element)) {
        if (queue_is_empty(*q))
            return -1;
        queue_enqueue(&save, queue_front(*q));
        queue_dequeue(q);
        ++index;
    }
    return index;
}

void queue_insert_at(queue_t *queue, void *element, unsigned int at) {
    assert(queue);
    queue_t save = {NULL, NULL};
    int index = 0;
    while (!queue_is_empty(*queue) && index < at) {
        queue_enqueue(&save, queue_front(*queue));
        queue_dequeue(queue);
        ++index;
    }
    queue_enqueue(&save, element);
    *queue = save;
}

bool queue_is_equal(queue_t *first_queue, queue_t *second_queue, bool (*comparison_func)(void*, void*)) {
    assert(first_queue && second_queue);
    if (!comparison_func)
        comparison_func = &generic_ptr_is_equal;
    queue_t save = {NULL, NULL};
    unsigned int index_1 = 0, index_2 = 0;
    bool is_equal = true;
    while (!queue_is_empty(*first_queue) || !queue_is_empty(*second_queue)) {
        if (!queue_is_empty(*first_queue)) {
            queue_enqueue(&save, queue_front(*first_queue));
            queue_dequeue(first_queue);
            ++index_1;
        }
        if (!queue_is_empty(*second_queue)) {
            queue_enqueue(&save, queue_front(*second_queue));
            queue_dequeue(second_queue);
            ++index_2;
        }
    }
    is_equal = index_1 == index_2;
    while (!queue_is_empty(save)) {
        if (index_1 > 0) {
            queue_enqueue(first_queue, queue_front(save));
            queue_dequeue(&save);
            --index_1;
        }
        if (index_2 > 0) {
            queue_enqueue(second_queue, queue_front(save));
            queue_dequeue(&save);
            ++index_2;
        }
        if (is_equal && !comparison_func(queue_back(*first_queue), queue_back(*second_queue)))
            is_equal = false;
    }
    return is_equal;
}

unsigned int queue_lenght(queue_t *queue) {
    assert(queue);
    queue_t save = {NULL, NULL};
    unsigned int lenght = 0;
    while (!queue_is_empty(*queue)) {
        queue_enqueue(&save, queue_front(*queue));
        queue_dequeue(queue);
        ++lenght;
    }
    *queue = save;
    return lenght;
}

