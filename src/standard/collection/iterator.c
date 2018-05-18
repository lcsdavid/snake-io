#include "iterator.h"

typedef struct iterator {
    const void *collection;
    void *state;
    iterator_destroy_state_func destroy;
    iterator_has_data_func has_data;
    iterator_data_func data;
    iterator_next_func next;
} iterator_t;

typedef void *(*iterator_create_state_func)(const void *, va_list);

typedef void (*iterator_destroy_state_func)(void *);

typedef bool (*iterator_has_data_func)(const void *);

typedef void *(*iterator_data_func)(void *);

typedef void *(*iterator_next_func)(void *);

const size_t iterator_size = sizeof(iterator_t);

void iterator_init(iterator_t *iterator, iterator_destroy_state_func destroy, iterator_has_data_func has_data,
                   iterator_data_func data, iterator_next_func next, const void *collection, void *state) {
    iterator->destroy = destroy;
    iterator->has_data = has_data;
    iterator->data = data;
    iterator->next = next;
    iterator->collection = collection;
    iterator->state = state;
}

iterator_t *
iterator_create(iterator_create_state_func create, iterator_destroy_state_func destroy, iterator_has_data_func has_data,
                iterator_data_func data, iterator_next_func next, const void *collection, ...) {
    iterator_t *iterator = calloc(1, sizeof(*iterator));
    if (iterator) {
        va_list ap;
        void *state;
        va_start(ap, collection);
        state = create(collection, ap);
        va_end(ap);
        if (state) {
            iterator_init(iterator, destroy, has_data, data, next, collection, state);
        } else {
            free(iterator);
            iterator = NULL;
        }
    }
    return iterator;
}

void iterator_erase(iterator_t *iterator) {
    if (iterator->destroy)
        iterator->destroy(iterator->state);
}

void iterator_destroy(iterator_t *iterator) {
    iterator_erase(iterator);
    free(iterator);
}

bool iterator_has_data(const iterator_t *iterator) {
    return iterator->has_data(iterator->state);
}

void *iterator_data(iterator_t *iterator) {
    return iterator->data(iterator->state);
}

iterator_t *iterator_next(iterator_t *iterator) {
    void *state = iterator->next(iterator->state);
    if (state)
        iterator->state = state;
    else
        iterator = NULL;
    return iterator;
}