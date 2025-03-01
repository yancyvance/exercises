#include <stdio.h>
#include <stdlib.h>
#define NULL_MARKER -100

// Sample C Implementation of a Stack using an array.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-01.

typedef struct StackArr_s {
    int top;
    int capacity;
    int *array;
} StackArr;


// maintenance
StackArr * create_stack(int);
void destroy_stack(StackArr *);

// function prototypes
void push(StackArr *, int);
int pop(StackArr *);
int peek(StackArr *);
int is_empty(StackArr *);
int is_full(StackArr *);


int main(void) {
    StackArr *stack = create_stack(10);
    int x;

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    while(!is_empty(stack)) {
        x = pop(stack);
        printf("%d\n", x);
    }

    push(stack, 40);

    while(!is_empty(stack)) {
        x = pop(stack);
        printf("%d\n", x);
    }

    destroy_stack(stack);

    return 0;
}


// function definitions
StackArr * create_stack(int capacity) {
    // dynamically allocate the stack
    StackArr *stack = malloc(sizeof(StackArr));

    // initialize the values of the members
    // and dynamically allocate the actual array
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = malloc(sizeof(int) * capacity);

    return stack;
}

void destroy_stack(StackArr *stack) {
    // deallocate the array
    free(stack->array);

    stack->array = NULL;

    // deallocate the stack itself
    free(stack);
}


void push(StackArr *stack, int val) {
    // we can only add a new element if there
    // is still space or if capacity is not yet
    // reached
    if(!is_full(stack)) {
        // find the next available space
        // in the array and put the element
        // there
        stack->array[++stack->top] = val;
    }
}


int pop(StackArr *stack) {
    // check first if the stack is empty
    if(!is_empty(stack)) {
        // return the top most element then
        // decrement the top index value
        // afterward
        return stack->array[stack->top--];
    }

    // special marker?
    return NULL_MARKER;
}


int peek(StackArr *stack) {
    // check if the stack is not empty
    // since this may cause an array index
    // out of bounds if it is
    if(!is_empty(stack)) {
        return stack->array[stack->top];
    }

    // possibly return marker?
    return NULL_MARKER;
}


int is_empty(StackArr *stack) {
    // check if the index is not
    // a valid one
    return stack->top == -1;
}


int is_full(StackArr *stack) {
    // check if all the spaces are used up
    // by looking at where the top is currently
    // pointing at right now
    return stack->top+1 == stack->capacity;
}
