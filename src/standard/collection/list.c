#include "list.h"

typedef struct node node_t;

typedef struct node {
    node_t *next;
    node_t *previous;
    void *data;
} node_t;

/* Principal */

void node_init(node_t *node, node_t *next, node_t *previous, void *data) {
    assert(node);
    node->next = next;
    node->previous = previous;
    node->data = data;
}

node_t *node_create(node_t *next, node_t *previous, void *data) {
    node_t *node = calloc(1, sizeof(node_t));
    if(!node) {
        perror("calloc():");
        return NULL;
    }
    node_init(node, next, previous, data);
    return node;
}

node_t *node_copy(const node_t *node) {
    assert(node);
    return node_create(NULL, NULL, node->data);
}

void node_delete(node_t *node) {
    assert(node);
    free(node->data);
    free(node);
}

/* Complements */

bool node_empty(const node_t *node) {
    assert(node);
    return node->data == NULL;
}

////////////////////////////////////////////////////////////////////////////////////

void list_init(list_t *list) {
    assert(list);
    list->front = list->back = NULL;
}

/* Access */

void* list_front(const list_t *list) {
    assert(list && list_empty(list));
    return list->front->data;
}

void* list_back(const list_t *list) {
    assert(list && list_empty(list));
    return list->back->data;
}

void* list_element_at(const list_t *list, size_t at) {
    assert(list);
    node_t *current_node = list->front;
    while (current_node->next && at > 0) {
        current_node = current_node->next;
        at--;
    }
    return current_node;
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
    node_t *before_current_node = NULL;
    node_t *current_node = list->front;
    while (current_node->next) {
        before_current_node = current_node;
        current_node = current_node->next;
    }
    node_delete(current_node);
    list->back = before_current_node;
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

void for_each(list_t *list, void (*consumer)(void*)) {
    assert(list && consumer);
    node_t* current_node = list->front;
    while (current_node) {
        (*consumer)(current_node->data);
        current_node = current_node->next;
    }
}


/* ... */
