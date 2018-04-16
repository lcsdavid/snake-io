#include "stack.h"

/* Stack primitive functions */

void *stack_top(stack_t stack) {
    if(!stack_is_empty(stack))
        return NULL;
    return stack->data;
}

void stack_push(stack_t *stack, void *data) {
    assert(stack);
    *stack = node_create(*stack, data);
}

void stack_pop(stack_t *stack) {
    assert(stack);
    if(*stack != NULL) {
        node_t *node = *stack;
        *stack = node->next;
        node_delete(node);
    }
}

int8_t stack_is_empty(stack_t stack) { return stack == NULL; }

/* Stack complementary functions */

unsigned int stack_height(stack_t *stack) {
    assert(stack);
    stack_t save = NULL;
    unsigned int index = 0;
    while (!stack_is_empty(*stack)) {
        stack_push(&save, stack_top(*stack));
        stack_pop(stack);
        ++index;
    }
    while (!stack_is_empty(save)) {
        stack_push(stack, stack_top(save));
        stack_pop(&save);
    }
    return index;
}

void *stack_element_at(stack_t *stack, unsigned int at) {
    assert(stack);
    stack_t save = NULL;
    unsigned int index = 0;
    while (!stack_is_empty(*stack) && index < at) {
        stack_push(&save, stack_top(*stack));
        stack_pop(stack);
        ++index;
    }
    void* element_at = stack_top(*stack);
    while (!stack_is_empty(save)) {
        stack_push(stack, stack_top(save));
        stack_pop(&save);
    }
    return element_at;
}

void stack_empty(stack_t *stack) {
    assert(stack);
    while(!stack_is_empty(*stack))
        stack_pop(stack);
}

void stack_copy(stack_t *source, stack_t *copy) {
    assert(source && copy);
    if (!stack_is_empty(*copy))
        stack_empty(copy);
    stack_t reversed_save = NULL;
    while (!stack_is_empty(*source)) {
        stack_push(&reversed_save, stack_top(*source));
        stack_pop(source);
    }
    while(!stack_is_empty(reversed_save)) {
        stack_push(source, stack_top(reversed_save));
        stack_push(copy, stack_top(reversed_save));
        stack_pop(&reversed_save);
    }
}

void stack_insert_at(stack_t *stack, void *element, unsigned int at) {
    assert(stack);
    stack_t save = NULL;
    unsigned int index = 0;
    while (!stack_is_empty(*stack) && index < at) {
        stack_push(&save, stack_top(*stack));
        stack_pop(stack);
        ++index;
    }
    stack_push(stack, element);
    while (!stack_is_empty(save)) {
        stack_push(stack, stack_top(save));
        stack_pop(&save);
    }
}

int8_t stack_is_equal(stack_t *stack_1, stack_t *stack_2, int8_t (*comparison_func)(void*, void*)) {
    assert(stack_1 && stack_2);
    if(!comparison_func)
        comparison_func = &generic_ptr_is_equal;
    stack_t save = NULL;
    unsigned int index_1 = 0, index_2 = 0;
    while (!stack_is_empty(*stack_1) || !stack_is_empty(*stack_2)) {
        if(!stack_is_empty(*stack_1)) {
            stack_push(&save, stack_top(*stack_1));
            stack_pop(stack_1);
            ++index_1;
        }
        if(!stack_is_empty(*stack_2)) {
            stack_push(&save, stack_top(*stack_2));
            stack_pop(stack_2);
            ++index_2;
        }
    }
    int8_t is_equal = index_1 == index_2;
    while (!stack_is_empty(save)) {
        if (index_1 > 0) {
            stack_push(stack_1, stack_top(save));
            stack_pop(&save);
            --index_1;
        }
        if (index_2 > 0) {
            stack_push(stack_2, stack_top(save));
            stack_pop(&save);
            --index_2;
        }
        if(is_equal && comparison_func(stack_top(*stack_1), stack_top(*stack_2)))
            is_equal = 0;
    }
    return is_equal;
}
