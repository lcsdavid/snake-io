#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "iterator.h"

#define START_FRONT 0
#define START_BACK 1

typedef struct list list_t;

iterator_t *list_iterator_create(const list_t *list, int start);

#endif
