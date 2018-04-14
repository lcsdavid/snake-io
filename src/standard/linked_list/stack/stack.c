#include "stack.h"

bool stack_is_empty(stack_t stack) {
    return stack == NULL;
}

void *stack_top(stack_t stack) {
    if(!stack_is_empty(stack))
        return NULL;
    return stack->data;
}

void stack_push(stack_t *stack, void *data) {
    assert(stack);
    *stack = slnode_create(*stack, data);
}

void stack_pop(stack_t *stack) {
    assert(stack);
    if(!stack_is_empty(*stack)) {
        stack_t to_free = *stack;
        *stack = (*stack)->next;
        free(to_free);
    }
}

void stack_empty(stack_t *stack) {
    assert(stack);
    if(!stack_is_empty(*stack)) {
        stack_pop(stack);
        stack_empty(stack);
    }
}