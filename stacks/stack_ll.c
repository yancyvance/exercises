#include <stdio.h>
#include <stdlib.h>
#define NULL_MARKER -100

// Sample C Implementation of a Stack using a linked list.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-01.

typedef struct LLNode_s {
    int data;
    struct LLNode_s *next;
} LLNode;

typedef struct StackLL_s {
    LLNode *top;
} StackLL;


// maintenance
StackLL * create_stack();
void destroy_stack(StackLL *);

// function prototypes
void push(StackLL *, int);
LLNode * pop(StackLL *);
LLNode * peek(StackLL *);
int is_empty(StackLL *);


int main(void) {
    StackLL *stack = create_stack();
    LLNode *x;

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    while(!is_empty(stack)) {
        x = pop(stack);
        printf("%d\n", x->data);

        // deallocate
        free(x);
    }

    push(stack, 40);

    while(!is_empty(stack)) {
        x = pop(stack);
        printf("%d\n", x->data);

        // deallocate
        free(x);
    }

    destroy_stack(stack);

    return 0;
}


// function definitions
StackLL * create_stack() {
    // dynamically allocate the stack
    StackLL *stack = malloc(sizeof(StackLL));

    // set the top to NULL
    stack->top = NULL;

    return stack;
}

void destroy_stack(StackLL *stack) {
    // deallocate the stack itself
    free(stack);
}


void push(StackLL *stack, int val) {
    // this is a copy of the linked list
    // add to head code (with changed variable names)

    // this new node will become the new head of the list
    LLNode *tmp = malloc(sizeof(LLNode));
    tmp->data = val;

    // next node of this new node will be whatever
    // used to be the head of the list
    // it can be an actual node OR NULL (empty list)
    tmp->next = stack->top;

    // list will have a new head
    stack->top = tmp;
}


LLNode * pop(StackLL *stack) {
    // this is a copy of the linked list
    // remove head code (with changed variable names)

    // check if the list is empty
    if( is_empty(stack) ) {
        return NULL;
    }

    // create a temporary pointer to the
    // current head node because this will
    // be removed from the list shortly
    // and we want to keep reference
    LLNode *tmp = stack->top;

    // update the head so that the new head
    // is the next to the current head
    stack->top = stack->top->next;

    // probably do some cleanup?
    tmp->next = NULL;

    // return the reference to the old head
    return tmp;
}


LLNode * peek(StackLL *stack) {
    // return a pointer to the top node
    return stack->top;
}


int is_empty(StackLL *stack) {
    // check if the top node is
    // currently a NULL
    return stack->top == NULL;
}
