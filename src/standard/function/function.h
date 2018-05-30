#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdbool.h>
#include <stdint.h>


typedef void *(*function)(void*);
typedef void *(*bi_function)(void*, void*);

typedef void (*consumer)(void*);
typedef void (*bi_consumer)(void*, void*);

typedef bool (*predicate)(void* a);

bool generic_ptr_equal(void* a, void* b);

#endif
