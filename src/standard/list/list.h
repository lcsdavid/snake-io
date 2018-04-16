#ifndef SNAKE_IO_LIST_H
#define SNAKE_IO_LIST_H

#include <stdbool.h>

#include "../node/node.h"

typedef struct list {
    node_t *front;
    node_t *back;
} list_t ;

/* Access */

void* list_front(const list_t *list);

void* list_back(const list_t *list);

void* list_element_at(const list_t *list);

/* Capacity */

bool list_empty(const list_t *list);

size_t list_size(const list_t *list);

/* Modifiers */

void list_clear(list_t *list);

void list_insert_at(list_t *list, void *element);

void list_erase_at(list_t *list, unsigned int index);

void list_push_back(list_t *list, void *element);

void list_pop_back(list_t *list);

void list_push_front(list_t *list, void *element);

void list_pop_front(list_t *list);

/* Operations */

/* ... */







#endif