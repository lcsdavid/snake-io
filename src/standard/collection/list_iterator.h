#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

typedef struct iterator iterator_t;
typedef struct list list_t;

void list_iterator_init(iterator_t *iterator, list_t *list);

iterator_t *list_iterator_create(list_t *list);

#endif
