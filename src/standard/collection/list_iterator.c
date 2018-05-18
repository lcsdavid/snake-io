#include "list_iterator.h"

#include "iterator.h"
#include "list.h"

void *list_iterator_state_create(const void *list, va_list ap) {
    return ((list_t *) list)->front;
}

void list_iterator_state_destroy(void *state) {}

static bool list_iterator_has_data(const void *state) {
    return state != NULL;
}

void *list_iterator_data(void *state) {
    return ((node_t *) state)->data;
}

static void *list_iterator_next(void *state) {
    return ((node_t *) state)->next;
}

void list_iterator_init(iterator_t *iterator, list_t *list) {
    iterator_init(iterator, list_iterator_state_destroy, list_iterator_has_data, list_iterator_data, list_iterator_next,
                  NULL, list);
}

iterator_t *list_iterator_create(list_t *list) {
    return iterator_create(list_iterator_state_create, list_iterator_state_destroy, list_iterator_has_data, list_iterator_data, list_iterator_next, list);
}