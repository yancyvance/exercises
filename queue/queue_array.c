#include <stdio.h>
#include <stdlib.h>
#define NULL_MARKER -100

// Sample C Implementation of a Queue using an array (naive).
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-01.

typedef struct QueueArr_s {
    int rear;
    int capacity;
    int *array;
} QueueArr;


// maintenance
QueueArr * create_queue(int);
void destroy_queue(QueueArr *);

// function prototypes
void enqueue(QueueArr *, int);
int dequeue(QueueArr *);
int peek(QueueArr *);
int is_empty(QueueArr *);
int is_full(QueueArr *);


int main(void) {
    QueueArr *queue = create_queue(5);
    int x;

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    while( !is_empty(queue) ) {
        x = dequeue(queue);
        printf("%d\n", x);
    }

    enqueue(queue, 40);

    while( !is_empty(queue) ) {
        x = dequeue(queue);
        printf("%d\n", x);
    }

    destroy_queue(queue);

    return 0;
}


// function definitions
QueueArr * create_queue(int capacity) {
    // dynamically allocate the queue
    QueueArr *queue = malloc(sizeof(QueueArr));

    // initialize the values of the members
    // and dynamically allocate the actual array
    queue->rear = -1;
    queue->capacity = capacity;
    queue->array = malloc(sizeof(int) * capacity);

    return queue;
}

void destroy_queue(QueueArr *queue) {
    // deallocate the array
    free(queue->array);

    queue->array = NULL;

    // deallocate the stack itself
    free(queue);
}


void enqueue(QueueArr *queue, int val) {
    // we can only add a new element if there
    // is still space or if capacity is not yet
    // reached
    if( !is_full(queue) ) {
        // find the next available space
        // in the array and put the element
        // there
        queue->array[++queue->rear] = val;
    }
}


int dequeue(QueueArr *queue) {
    // check first if the stack is empty
    if( !is_empty(queue) ) {
        int tmp = queue->array[0];

        // do a shift to the left by one
        // since there is a gap
        for(int i = 0; i < queue->rear; i++) {
            queue->array[i] = queue->array[i+1];
        }

        // decrement the rear index
        // because we shifted by one slot
        --queue->rear;

        // return the top most element then
        // decrement the top index value
        // afterward
        return tmp;
    }

    // special marker?
    return NULL_MARKER;
}


int peek(QueueArr *queue) {
    // check if the stack is not empty
    // since this may cause an array index
    // out of bounds if it is
    if( !is_empty(queue) ) {
        // we are assuming that the front
        // is always at index 0
        return queue->array[0];
    }

    // possibly return marker?
    return NULL_MARKER;
}


int is_empty(QueueArr *queue) {
    // check if the index is not
    // a valid one
    return queue->rear == -1;
}


int is_full(QueueArr *queue) {
    // check if all the spaces are used up
    // by looking at where the top is currently
    // pointing at right now
    return queue->rear+1 == queue->capacity;
}
