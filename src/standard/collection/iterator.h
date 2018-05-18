#ifndef SNAKE_IO_ITERATOR_H
#define SNAKE_IO_ITERATOR_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct iterator {
    const void *collection;
} iterator_t;

typedef void *(*iterator_create_state_func)(const void *, va_list);
typedef void (*iterator_destroy_state_func)(void *);
typedef bool (*iterator_has_data_func)(const void *);
typedef void *(*iterator_data_func)(void *);
typedef void *(*iterator_next_func)(void *);

extern const size_t iterator_size;

#endif