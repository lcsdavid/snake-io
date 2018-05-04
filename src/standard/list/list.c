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
    if(at == 0)
        list_push_front(list, element);
    node_t *current_node = list->front;
    while (--at > 1 && current_node->next) current_node = current_node->next;
    if(!current_node->next) {
        current_node->next = node_create(NULL, element);
        list->back = current_node->next;
    } else
        current_node->next = node_create(current_node->next->next, element);
}

void list_erase_at(list_t *list, size_t at) {
    assert(list);
    if(at == 0)
        list_pop_front(list);
    node_t *current_node = list->front;
    while (--at > 1 && current_node->next) current_node = current_node->next;
    if(current_node->next) {
        node_t *node_to_delete = current_node->next;
        current_node->next = current_node->next->next;
        node_delete(node_to_delete);
    }
}

void list_push_back(list_t *list, void *element) {
    assert(list);
    if(list->back) {
        list->back->next = node_create(NULL, element);
        list->back = list->back->next;
    } else
        list->front = list->back = node_create(NULL, element);
}

void list_pop_back(list_t *list) {
    assert(list);
    if (list_empty(list))
        return;
    node_t *current_node = list->front;
    while (current_node->next) current_node = current_node->next;
    node_delete(current_node->next);
    list->back = current_node;
}

void list_push_front(list_t *list, void *element) {
    assert(list);
    list->front = node_create(list->front, element);
    if(!list->back)
        list->back = list->front;
}

void list_pop_front(list_t *list) {
    assert(list);
    if(list->front) {
        if(list->front->next) {
            node_t *new_front_node = list->front->next;
            node_delete(list->front);
            list->front = new_front_node;
        } else {
            node_delete(list->front);
            list->front = list->back = NULL;
        }
    }
}

/* Operations */

void for_each(list_t *list, void (*func)(void*)) {
    assert(list && func);
    node_t* current_node = list->front;
    while (current_node) {
        func(current_node->data);
        current_node = current_node->next;
    }
}


/* ... */
