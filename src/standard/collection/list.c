#include "list.h"

#include "node.h"

void list_init(list_t *list) {
    assert(list);
    list->front = list->back = NULL;
    list->size = 0;
}

/* Access */

void *list_front(const list_t *list) {
    assert(list && !list_empty(list));
    return list->front->data;
}

void *list_back(const list_t *list) {
    assert(list && !list_empty(list));
    return list->back->data;
}

void *list_element_at(const list_t *list, size_t at) {
    assert(list && at < list->size);
    node_t *current_node;
    if (at * 2 <= list->size) {
        current_node = list->front;
        for (size_t i = 0; i < at; i++)
            current_node = current_node->next;
    } else {
        current_node = list->back;
        for (size_t i = list->size; i > at; i--)
            current_node = current_node->previous;
    }
    return current_node->data;
}

/* Capacity */

bool list_empty(const list_t *list) {
    assert(list);
    return list->size == 0;
}

size_t list_size(const list_t *list) {
    assert(list);
    return list->size;
}

/* Modifiers */

void list_clear(list_t *list) {
    assert(list);
    node_t *current_node = list->front;
    while (current_node) {
        node_t *node = current_node;
        current_node = current_node->next;
        node_delete(node);
    }
    list->front = list->back = NULL;
    list->size = 0;
}

void list_insert_at(list_t *list, void *element, size_t at) {
    assert(list);
    if (at < list->size)
        return;
    // TODO
}

void list_erase_at(list_t *list, size_t at) {
    assert(list);
    if (at > list->size)
        return;
    node_t *current_node;
    if (at * 2 <= list->size) {
        current_node = list->front;
        for (size_t i = 0; i < at; i++)
            current_node = current_node->next;
    } else {
        current_node = list->back;
        for (size_t i = list->size; i > at; i--)
            current_node = current_node->previous;
    }
    if (current_node->previous)
        current_node->previous->next = current_node->next;
    if (current_node->next)
        current_node->next->previous = current_node->previous;
    list->size--;
    node_delete(current_node);
}

void list_push_back(list_t *list, void *element) {
    assert(list);
    if (list->back) {
        list->back->next = node_create(list->back, NULL, element);
        list->back = list->back->next;
    } else
        list->front = list->back = node_create(NULL, NULL, element);
    list->size++;
}

void list_pop_back(list_t *list) {
    assert(list);
    if (!list->back)
        return;
    node_t *pop_back = list->back;
    if (list->back->previous) {
        list->back = list->back->previous;
        list->back->next = NULL;
    } else
        list->front = list->back = NULL;
    list->size--;
    node_delete(pop_back);
}

void list_push_front(list_t *list, void *element) {
    assert(list);
    if (list->front) {
        list->front->previous = node_create(NULL, list->front, element);
        list->front = list->front->previous;
    } else
        list->back = list->front = node_create(NULL, NULL, element);
    list->size++;
}

void list_pop_front(list_t *list) {
    assert(list);
    if (!list->front)
        return;
    node_t *pop_front = list->front;
    if (list->front->next) {
        list->front = list->front->next;
        list->front->previous = NULL;
    } else
        list->front = list->back = NULL;
    list->size--;
    node_delete(pop_front);
}

/* Operations */

void for_each(list_t *list, void (*consumer)(void *)) {
    assert(list && consumer);
    node_t *current_node = list->front;
    while (current_node) {
        consumer(current_node->data);
        current_node = current_node->next;
    }
}

/* ... */
