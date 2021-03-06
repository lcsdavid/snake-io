#ifndef STACK_H
#define STACK_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "../function/function.h"

typedef struct forward_node forward_node_t;

/**
 * @typedef stack_t
 * @brief Collection of elements.
 *
 * stack_t is a collection of elements.
 * The main operations ("modifiers") are:
 *   - push, which adds an element to the collection,
 *   - pop, which removes the most recently added element that was not yet removed.
 */
typedef forward_node_t* stack_t;

/* Access */

/**
 * Top returns the value of the top ("head") of the collection without removing the element from the collection.
 * @remark stack_t primitive function.
 * @param stack Collection of element.
 * @return Head of the stack.
 */
void *stack_top(stack_t stack);

/* Capacity */

/**
 * @remark stack_t primitive function.
 * @param stack Stack to evaluate.
 * @return If stack is empty. 1 for 'empty', 0 for 'not empty'.
 */
bool stack_empty(stack_t stack);

/* Modifiers */

/**
 * Push adds an element to the collection.
 * @remark stack_t primitive function.
 * @param stack Pointer on collection of element. Can't be null.
 * @param data Value to push.
 */
void stack_push(stack_t *stack, void *data);

/**
 * Pop removes the most recently added element that was not yet removed.
 * @remark stack_t primitive function.
 * @param stack Pointer on collection of element. Can't be null.
 */
void stack_pop(stack_t *stack);

/* Operations */

/**
 * @brief Empty the stack.
 * @param stack Pointer on collection of element. Can't be null.
 */
void stack_clear(stack_t *stack);

/**
 * @brief Copies a collection.
 * Copies a collection without altering it.
 * @param source Source collection.
 * @param copy Pointer on collection copy.
 */
void stack_copy(stack_t *source, stack_t *copy);

void *stack_element_at(stack_t *stack, size_t at);

/**
 * @brief Determines if two collections are the same.
 * Determines if two collections are the same without altering both.
 * Comparison is generic pointer comparison if no comparison_func is specified.
 * @param first_stack Pointer on first collection. Can't be null.
 * @param second_stack Pointer on second collection. Can't be null.
 * @param comparison_func Function which compares two generic pointers values.
 * @return is_equal.
 */
bool stack_equal(stack_t *first_stack, stack_t *second_stack, bool (*_type_equal_func)(void*, void*));

/**
 * @brief Gives the size ("height") of the collection ("stack").
 * Gives the size ("height") of the collection ("stack") without altering it.
 * @param stack Pointer on collection. Can't be null.
 * @return Height.
 */
size_t stack_height(stack_t *stack);

void stack_insert_at(stack_t *stack, void *element, size_t at);

#endif