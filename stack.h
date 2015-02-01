/*
 * Small. Unbreakable. Rational. Fast.
 * This program is public domain.
 * Author: Michel Chevalier (2015)
 *
 * stack functions for stack local use within single-threaded function. consume popped items before any other pushes.
 */

#ifndef STACK_H
#define STACK_H

/* STACK_PUSH: Push a string to a stack.
   stack_ptr: current position in stack
   push: string to push to the stack (will be copied into the stack)
   end_of_stack: maximum permissible value of stack_ptr
   RETURNS: new value of stack_ptr.
*/
char *STACK_PUSH(char *stack_ptr, char *push, char *end_of_stack);

/* STACK_POP: Pop a string from a stack.
   stack_ptr: current position in stack.
   start_of_stack: minimum permissible value of stack_ptr
   RETURNS: new value of stack_ptr, pointing to string which has been 'popped'.
   Consume immediately, as will be over-written by next STACK_PUSH.
*/
char *STACK_POP(char *stack_ptr, char *start_of_stack);

/* STACKCAT: Concatenate two strings onto a stack.
   stack_ptr: current position in stack.
   push1: first string to push
   push2: second string to push
   end_of_stack: maximum permissible value of stack_ptr
   RETURNS: new value of stack_ptr
   You will need to STACK_POP to retrieve the result.
*/
char *STACKCAT(char *stack_ptr, char *push1, char *push2, char *end_of_stack);

/* STACK_CMP: Compare a string with a string on the stack.
   stack_ptr: current position in stack.
   cmp: string to compare with.
   end_of_stack: maximum permissible value of stack_ptr
   RETURNS: 0 for match, 1 no match.
*/
int STACKCMP(char *stack_ptr, const char *cmp, char *end_of_stack);

#endif
