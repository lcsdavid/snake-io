#ifndef STACK_H
#define STACK_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#include "../node/slnode.h"

typedef struct {
    slnode_t *head;
    size_t size;
} stack_t;

const stack_t stack_default = {(void *) 0, 0};

stack_t *stack_create();

void stack_delete(stack_t *stack);

bool stack_empty(const stack_t *stack);

void *stack_top(const stack_t *stack);

void stack_push_back(stack_t *stack, void *data);

void stack_pop_back(stack_t *stack);

#endif