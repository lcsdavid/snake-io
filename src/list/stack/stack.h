#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    node_t* next;
    void* data;
} node_t ;

typedef struct {
    node_t* head;
    size_t size;
} stack_t ;

stack_t* stack_create();

void stack_delete(stack_t* stack);

bool empty(const stack_t* stack);

void* stack_top(const stack_t* stack);

void stack_push(stack_t* stack, void* data);

void stack_pop(stack_t* stack);






#endif