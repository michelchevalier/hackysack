/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 *
 * stack functions for stack local use within single-threaded function. consume popped items before any other pushes.
 */

#include <stddef.h>
#include "stack.h"

char *STACK_PUSH(char *stack_ptr, char *push, char *end_of_stack)
{
    if ((stack_ptr == end_of_stack) || !push) {
        return NULL;
    }
    while (*push && (stack_ptr < end_of_stack)) {
        *stack_ptr++ = *push++;
    }
    if (stack_ptr == end_of_stack) {
        return NULL;
    }
    *stack_ptr++ = '\0';
    return stack_ptr;
}

char *STACK_POP(char *stack_ptr, char *start_of_stack)
{
    if (stack_ptr == start_of_stack) {
        return NULL;
    }
    stack_ptr -= 2;
    while (*stack_ptr && (stack_ptr >= start_of_stack)) { stack_ptr--; }
    return stack_ptr + 1;
}

char *STACKCAT(char *stack_ptr, char *push1, char *push2, char *end_of_stack)
{
    char *retval;

    retval = STACK_PUSH(stack_ptr, push1, end_of_stack);
    if (!retval) {
        return retval;
    }
    retval--;
    retval = STACK_PUSH(retval, push2, end_of_stack);
    return retval;
}

int STACKCMP(char *stack_ptr, const char *cmp, char *end_of_stack)
{
    if ((stack_ptr == end_of_stack) || !cmp ) {
        return 1;
    }
    while (*cmp && (stack_ptr < end_of_stack)) {
        if (!(*stack_ptr++ == *cmp++)) {
            return 1;
        }
    }
    return 0;
}
