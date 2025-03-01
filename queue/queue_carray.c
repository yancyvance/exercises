#include <stdio.h>
#include <stdlib.h>
#define NULL_MARKER -100

// Sample C Implementation of a Queue using an array (circular).
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-01.

typedef struct QueueCArr_s {
    int front;
    int rear;
    int capacity;
    int *array;
} QueueCArr;


// maintenance
QueueCArr * create_queue(int);
void destroy_queue(QueueCArr *);

// function prototypes
void enqueue(QueueCArr *, int);
int dequeue(QueueCArr *);
int peek(QueueCArr *);
int is_empty(QueueCArr *);
int is_full(QueueCArr *);


int main(void) {
    QueueCArr *queue = create_queue(5);
    int x;

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);

    x = dequeue(queue);
    printf("%d\n", x);

    x = dequeue(queue);
    printf("%d\n", x);

    enqueue(queue, 60);
    enqueue(queue, 70);

    // empty the queue
    while( !is_empty(queue) ) {
        x = dequeue(queue);
        printf("%d\n", x);
    }

    destroy_queue(queue);

    return 0;
}


// function definitions
QueueCArr * create_queue(int capacity) {
    // dynamically allocate the queue
    QueueCArr *queue = malloc(sizeof(QueueCArr));

    // initialize the values of the members
    // and dynamically allocate the actual array
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->array = malloc(sizeof(int) * capacity);

    return queue;
}

void destroy_queue(QueueCArr *queue) {
    // deallocate the array
    free(queue->array);

    queue->array = NULL;

    // deallocate the stack itself
    free(queue);
}


void enqueue(QueueCArr *queue, int val) {
    // we can only add a new element if there
    // is still space or if capacity is not yet
    // reached
    if( !is_full(queue) ) {
        // find the next available space
        // in the array and put the element
        // there
        // compute the correct index
        int idx = (queue->rear + 1) % queue->capacity;

        // check if this queue was empty early
        if( is_empty(queue) ) {
            queue->front = queue->rear = idx;
        }
        else {
            // update the rear
            queue->rear = idx;
        }

        // set the value at that location
        queue->array[idx] = val;
    }
}


int dequeue(QueueCArr *queue) {
    // check first if the stack is empty
    if( !is_empty(queue) ) {
        int tmp = queue->array[queue->front];

        // check if this is also the rear
        // meaning there is only a single element
        // in the queue, if it is, then reset to 0
        if(queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        }
        else {
            // if not, then proceed with the circular
            // computation

            // compute the new front index after
            // moving to the right
            int idx = (queue->front + 1) % queue->capacity;

            // update the front index of the queue
            queue->front = idx;
        }

        // return the removed element
        return tmp;
    }

    // special marker?
    return NULL_MARKER;
}


int peek(QueueCArr *queue) {
    // check if the stack is not empty
    // since this may cause an array index
    // out of bounds if it is
    if( !is_empty(queue) ) {
        // we are assuming that the front
        // is always at index 0
        return queue->array[queue->front];
    }

    // possibly return marker?
    return NULL_MARKER;
}


int is_empty(QueueCArr *queue) {
    // check if the index is not
    // a valid one
    return queue->front == -1;
}


int is_full(QueueCArr *queue) {
    if( is_empty(queue) ) {
        return 0;
    }

    // check if which case it is
    // if rear is to the right of front
    if(queue->front < queue->rear) {
        // simply just get the difference
        // and compare it with the capacity
        int size = queue->rear - queue->front;

        return size+1 == queue->capacity;
    }
    else {
        // if it is the other way around, simply
        // check if adding one more to the rear
        // will yield the front
        return queue->rear+1 == queue->front;
    }
}
