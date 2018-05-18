#include "iterator.h"
#include "list.h"

iterator_t *list_iterator_create(void *list) {
    return iterator_create(list, NULL, list_iterator_has_next, list_iterator_next);
}

static bool list_iterator_has_data(const void *node) {
    return node != NULL;
}

void *list_iterator_data(node_t *state) {
    return state->data;
}

static void *list_iterator_next(node_t *state) {
    return state->next;
}