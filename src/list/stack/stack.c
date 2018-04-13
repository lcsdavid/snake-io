#include "stack.h"

stack_t* stack_create() {
    stack_t* stack = calloc(1, sizeof(stack_t));
    if(!stack) {
        perror("calloc()");
        return (void*)0;
    }
    stack->head;
    stack->size;
    return stack;
}

void stack_delete(stack_t* stack) {
    if(stack) {
        stack_pop_back(stack);
        stack_delete(stack);
        if(stack_empty(stack))
            free(stack);
    }
}

bool stack_empty(const stack_t* stack) {
    assert(stack);
    return stack->size < 1;
}

void* stack_top(const stack_t* stack) {
    assert(stack);
    if(stack_empty(stack))
        return (void*)0;
    node_t current_node = stack->head;
    while(current_node->next)
        current_node = current_node->next;
    return current_node->data;
}

void stack_push_back(stack_t* stack, void* data) {

}

void stack_pop_back(stack_t* stack) {

}