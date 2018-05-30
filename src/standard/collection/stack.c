#include "stack.h"

#include "forward_node.h"

/* Access */

void *stack_top(stack_t stack) {
    if(!stack_empty(stack))
        return NULL;
    return stack->data;
}

/* Capacity */

bool stack_empty(stack_t stack) { return stack == NULL; }

/* Modifiers */

void stack_push(stack_t *stack, void *data) {
    assert(stack);
    *stack = forward_node_create(*stack, data);
}

void stack_pop(stack_t *stack) {
    assert(stack);
    if(*stack != NULL) {
        forward_node_t *node = *stack;
        *stack = node->next;
        forward_node_delete(node);
    }
}

/* Operations */

void stack_clear(stack_t *stack) {
    assert(stack);
    while(!stack_empty(*stack))
        stack_pop(stack);
}

void stack_copy(stack_t *source, stack_t *copy) {
    assert(source && copy);
    if (!stack_empty(*copy))
        stack_clear(copy);
    stack_t reversed_save = NULL;
    while (!stack_empty(*source)) {
        stack_push(&reversed_save, stack_top(*source));
        stack_pop(source);
    }
    while(!stack_empty(reversed_save)) {
        stack_push(source, stack_top(reversed_save));
        stack_push(copy, stack_top(reversed_save));
        stack_pop(&reversed_save);
    }
}

void *stack_element_at(stack_t *stack, size_t at) {
    assert(stack);
    stack_t save = NULL;
    unsigned int index = 0;
    while (!stack_empty(*stack) && index < at) {
        stack_push(&save, stack_top(*stack));
        stack_pop(stack);
        ++index;
    }
    void* element_at = stack_top(*stack);
    while (!stack_empty(save)) {
        stack_push(stack, stack_top(save));
        stack_pop(&save);
    }
    return element_at;
}

bool stack_equal(stack_t *stack_1, stack_t *stack_2, bool (*_type_equal_func)(void*, void*)) {
    assert(stack_1 && stack_2);
    if(!_type_equal_func)
        _type_equal_func = &generic_ptr_equal;
    stack_t save = NULL;
    unsigned int index_1 = 0, index_2 = 0;
    while (!stack_empty(*stack_1) || !stack_empty(*stack_2)) {
        if(!stack_empty(*stack_1)) {
            stack_push(&save, stack_top(*stack_1));
            stack_pop(stack_1);
            ++index_1;
        }
        if(!stack_empty(*stack_2)) {
            stack_push(&save, stack_top(*stack_2));
            stack_pop(stack_2);
            ++index_2;
        }
    }
    bool is_equal = index_1 == index_2;
    while (!stack_empty(save)) {
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
        is_equal = is_equal && _type_equal_func(stack_top(*stack_1), stack_top(*stack_2));
    }
    return is_equal;
}

size_t stack_height(stack_t *stack) {
    assert(stack);
    stack_t save = NULL;
    size_t index = 0;
    while (!stack_empty(*stack)) {
        stack_push(&save, stack_top(*stack));
        stack_pop(stack);
        ++index;
    }
    while (!stack_empty(save)) {
        stack_push(stack, stack_top(save));
        stack_pop(&save);
    }
    return index;
}

void stack_insert_at(stack_t *stack, void *element, size_t at) {
    assert(stack);
    stack_t save = NULL;
    size_t index = 0;
    while (!stack_empty(*stack) && index < at) {
        stack_push(&save, stack_top(*stack));
        stack_pop(stack);
        ++index;
    }
    stack_push(stack, element);
    while (!stack_empty(save)) {
        stack_push(stack, stack_top(save));
        stack_pop(&save);
    }
}


