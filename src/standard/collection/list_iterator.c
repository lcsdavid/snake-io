#include "list_iterator.h"

#include "list.h"
#include "node.h"

#define START_FRONT 0
#define START_BACK 1

void *list_iterator_state_create(const void *list, va_list ap) {
    assert(list);
    int start = va_arg(ap, int);
    if(start == START_FRONT)
        return ((list_t*) list)->front;
    if(start == START_BACK)
        return ((list_t*) list)->back;
    return ((list_t*) list)->front;
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

static void *list_iterator_previous(void *state) {
    assert(state);
    return ((node_t*) state)->next;
}

static void *list_iterator_next(void *state) {
    assert(state);
    return ((node_t*) state)->next;
}

/* */

iterator_t *list_iterator_create(list_t *list) {
    return iterator_create(list_iterator_state_create, NULL, list_iterator_has_data, list_iterator_data,
                           list_iterator_previous, list_iterator_next, list, START_FRONT);
}

iterator_t *list_back_iterator_create(list_t *list) {
    return iterator_create(list_iterator_state_create, NULL, list_iterator_has_data, list_iterator_data,
                           list_iterator_previous, list_iterator_next, list, START_BACK);
}