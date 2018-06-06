#include "list_iterator.h"

#include "list.h"
#include "node.h"

void *list_front_iterator_state_create(const void *list, va_list ap) {
    assert(list);
    return (void *) list;
}

static bool list_iterator_has_data(const void *state) {
    return state != NULL;
}

static void *list_iterator_data(void *state) {
    if (state)
        return ((node_t*) state)->data;
    else
        return NULL;
}

static void *list_iterator_next(void *state) {
    assert(state);
    return ((node_t*) state)->next;
}

static void *list_iterator_previous(void *state) {
    assert(state);
    return ((node_t*) state)->previous;
}

/* */

iterator_t *list_iterator_create(const list_t *list, int start) {
    if(list_empty(list))
        return NULL;
    if(start == START_FRONT)
        return iterator_create(list_front_iterator_state_create, NULL, list_iterator_has_data, list_iterator_data,
                           list_iterator_next, list_iterator_previous, list->front);
    else if(start == START_BACK)
        return iterator_create(list_front_iterator_state_create, NULL, list_iterator_has_data, list_iterator_data,
                               list_iterator_next, list_iterator_previous, list->back);
    else
        return NULL;
}