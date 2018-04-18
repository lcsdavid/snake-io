#include "list.h"

/* Access */

void* list_front(const list_t *list) {
    assert(list);
    return list->front->data;
}

void* list_back(const list_t *list) {
    assert(list);
    return list->back->data;
}

void* list_element_at(const list_t *list, size_t at) {
    assert(list);
    node_t *current_node = list->front;
    while (--at > 0 && current_node) current_node = current_node->next;
    return current_node ? current_node->data : NULL;
}

/* Capacity */

bool list_empty(const list_t *list) {
    assert(list);
    return !list->front || !list->back;
}

size_t list_size(const list_t *list) {
    assert(list);
    size_t size = 0;
    node_t *current_node = list->front;
    while(current_node) {
        current_node = current_node->next;
        ++size;
    }
    return size;
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
    *list = (list_t){NULL, NULL};
}

void list_insert_at(list_t *list, void *element, size_t at) {
    assert(list);
    node_t *current_node = list->front;
    while (--at > 0 && current_node->next) current_node = current_node->next;
    if(!current_node->next) {
        current_node->next = node_create(NULL, element);
        list->back = current_node->next;
    } else
        current_node->next = node_create(current_node->next->next, element);
}

void list_erase_at(list_t *list, size_t at) {
    assert(list);
    node_t *current_node = list->front;
    while (--at > 0 && current_node->next) current_node = current_node->next;
    // TODO
}









/* Operations */

void for_each(list_t *list, void (*func)(void*)) {
    assert(list);
    node_t* current_node = list->front;
    while (current_node) {
        func(current_node->data);
        current_node = current_node->next;
    }
}


/* ... */
