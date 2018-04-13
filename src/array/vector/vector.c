#include "vector.h"

/* Constructor & destructor */
vector_t* vector_create_ptr(size_t capacity) {
    vector_t* vector = calloc(1, sizeof(vector_t));
    if(!vector) {
        perror("calloc()");
        return (void*)0;
    }
    vector->capacity = capacity;
    vector->size = 0;
    vector->data = calloc(capacity, sizeof(void*));
    if(!vector->data)
        perror("calloc()");
    return vector;
}

void vector_delete(vector_t* vector) {
    if(vector) {
        free(vector->data);
        free(vector);
    }
}

/* Capacity */
bool vector_empty(const vector_t* vector) {
    return !vector || vector->size < 1;
}

void vector_reserve(vector_t* vector, size_t new_capacity) {
    if(vector)
        if(vector->capacity < new_capacity) {
            vector->data = realloc(vector->data, sizeof(void*) * new_capacity);
            if(vector->data == (void*)0)
                perror("realloc()");
            else
                vector->capacity = new_capacity;
        }
}

/* Modifiers */
void vector_clear(vector_t* vector) {
    if(vector) {
        memset(vector->data, 0, sizeof(void *) * vector->capacity);
        vector->size = 0;
    }
}

void vector_insert(vector_t* vector, size_t pos, void* value) {
    if(vector)
        if(vector->size >= pos) {
            if(vector->capacity <= vector->size) {
                vector_reserve(vector, vector->capacity++);
            }
            if(vector->size > pos)
                memmove(&vector->data[pos], &vector->data[pos] + 1, vector->size - pos);
            vector->data[pos] = value;
            vector->size++;
        }
}

void vector_push_back(vector_t* vector, void* value) {
    if(vector) {
        if (vector->capacity <= vector->size)
            vector_reserve(vector, vector->capacity++);
        vector->data[vector->size] = value;
        vector->size++;
    }
}

void vector_pop_back(vector_t* vector) {
    if(vector) {
        if (!vector_empty(vector)) {
            vector->data[vector->size - 1] = (void *) 0;
            vector->size--;
        }
    }
}

void vector_resize(vector_t* vector, size_t new_capacity) {
    if(vector) {
        vector->data = realloc(vector->data, sizeof(void *) * new_capacity);
        if (vector->data == (void *) 0)
            perror("realloc()");
        else
            vector->capacity = new_capacity;
    }
}

