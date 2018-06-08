#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    void** data;
    size_t size;
    size_t capacity;
} vector_t;

/* Constructor & destructor */

vector_t vector_create(size_t capacity);

vector_t* vector_create_ptr(size_t capacity);

void vector_delete(vector_t* vector);

/* Capacity */

bool vector_empty(const vector_t* vector);

void vector_reserve(vector_t* vector, size_t new_capacity);

/* Modifiers */

void vector_clear(vector_t* vector);

void vector_insert(vector_t* vector, size_t pos, void* value);

void vector_push_back(vector_t* vector, void* value);

void vector_pop_back(vector_t* vector);

void vector_resize(vector_t* vector, size_t new_capacity);

#endif