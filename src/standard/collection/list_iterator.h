#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "iterator.h"

typedef struct list list_t;

iterator_t *list_iterator_create(list_t *list);

iterator_t *list_back_iterator_create(list_t *list);

#endif
