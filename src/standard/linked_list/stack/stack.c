#include "stack.h"

stack_t *stack_create() {
    stack_t *stack = calloc(1, sizeof(stack_t));
    if (!stack) {
        perror("calloc()");
        return (void *) 0;
    }
    stack = stack_create();
    return stack;
}

void stack_delete(stack_t *stack) {
    if (stack) {
        stack_pop_back(stack);
        stack_delete(stack);
        if (stack_empty(stack))
            free(stack);
    }
}

bool stack_empty(const stack_t *stack) {
    assert(stack);
    return stack->size < 1;
}

void *stack_top(const stack_t *stack) {
    assert(stack);
    if (stack_empty(stack))
        return (void *) 0;
    slnode_t *current_node = stack->head;
    while (current_node->next)
        current_node = current_node->next;
    return current_node->data;
}

void stack_push_back(stack_t *stack, void *data) {
    assert(stack);
    if (stack_empty(stack))
        stack->head = slnode_create((void *) 0, data);
    else {
        slnode_t *current_node = stack->head;
        while (current_node->next)
            current_node = current_node->next;
        current_node->next = slnode_create((void *) 0, data);
    }
    stack->size++;
}

void stack_pop_back(stack_t *stack) {
    assert(stack);
    if (!stack_empty(stack)) {
        if (stack->size > 1) {
            slnode_t *current_node = stack->head;
            while (current_node->next->next)
                current_node = current_node->next;
            free(current_node->next);
            current_node->next = (void *) 0;
        } else {
            free(stack->head);
            stack->head->next = (void *) 0;
        }
        stack->size--;
    }
}