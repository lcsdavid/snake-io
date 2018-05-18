#ifndef SNAKE_IO_ITERATOR_H
#define SNAKE_IO_ITERATOR_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct iterator iterator_t;

typedef void *(*iterator_create_state_func)(const void *, va_list);
typedef void (*iterator_destroy_state_func)(void *);
typedef bool (*iterator_has_data_func)(const void *);
typedef void *(*iterator_data_func)(void *);
typedef void *(*iterator_next_func)(void *);

void iterator_init(iterator_t *iterator, iterator_destroy_state_func destroy, iterator_has_data_func has_data,
                   iterator_data_func data, iterator_next_func next, const void *collection, void *state);

iterator_t *iterator_create(iterator_create_state_func create, iterator_destroy_state_func destroy, iterator_has_data_func has_data,
                            iterator_data_func data, iterator_next_func next, const void *collection, ...);

void iterator_destroy(iterator_t *iterator);

bool iterator_has_data(const iterator_t *iterator);

void *iterator_data(iterator_t *iterator);

iterator_t *iterator_next(iterator_t *iterator);

extern const size_t iterator_size;

#endif