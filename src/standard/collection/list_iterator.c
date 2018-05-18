#include "list_iterator.h"

#include "list.h"

void *list_iterator_state_create(const list_t *list, va_list ap) {
    assert(list);
    return list->front;
}

static bool list_iterator_has_data(const node_t *state) {
    return state != NULL;
}

void *list_iterator_data(node_t *state) {
    if (state)
        return state->data;
    else
        return NULL;
}

static void *list_iterator_next(node_t *state) {
    assert(state);
    return state->next;
}

void list_iterator_init(iterator_t *iterator, list_t *list) {
    iterator_init(iterator, NULL, (iterator_has_data_func) list_iterator_has_data,
                  (iterator_data_func) list_iterator_data, (iterator_next_func) list_iterator_next,
                  NULL, list);
}

iterator_t *list_iterator_create(list_t *list) {
    return iterator_create((iterator_create_state_func) list_iterator_state_create, NULL,
                           (iterator_has_data_func) list_iterator_has_data, (iterator_data_func) list_iterator_data,
                           (iterator_next_func) list_iterator_next, list);
}