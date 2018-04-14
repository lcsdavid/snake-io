#ifndef STACK_H
#define STACK_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#include "../node/slnode.h"

#define STACK_DEFAULT = NULL;

typedef slnode_t* stack_t;

/**
 *
 * @param stack Stack to evaluate.
 * @return If stack is empty. true for 'empty', false for 'not empty'.
 */
bool stack_is_empty(stack_t stack);

/**
 * Give the head of the stack.
 * @param stack Stack which you want to get the head.
 * @return Head of the stack.
 */
void *stack_top(stack_t stack);

/**
 * Push a new value on stack.
 * @param stack Pointer on stack to modify. Can't be null.
 * @param data Value to push.
 */
void stack_push(stack_t *stack, void *data);

/**
 * Pop the head.
 * @param stack  Pointer on stack to modify. Can't be null.
 */
void stack_pop(stack_t *stack);

/**
 * Empty the stack.
 * @param stack Pointer on stack to empty. Can't be null.
 */
void stack_empty(stack_t *stack);

// TODO
void stack_copy(stack_t source_stack, stack_t *new_stack);

// TODO
bool stack_is_equal(stack_t stack_one, stack_t stack_two);

// TODO
/**
 * Give the height of th stack.
 * @param stack Stack to evaluate. Not altered.
 * @return Height of the stack.
 */
size_t stack_size(stack_t stack);

#endif