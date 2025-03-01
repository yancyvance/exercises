#include <stdio.h>
#include <stdlib.h>

// Sample C Implementation of a Queue using a linked list.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-01.

typedef struct LLNode_s {
    int data;
    struct LLNode_s *next;
} LLNode;

typedef struct QueueLL_s {
    LLNode *front;
    LLNode *rear;
} QueueLL;


// maintenance
QueueLL * create_queue();
void destroy_queue(QueueLL *);

// function prototypes
void enqueue(QueueLL *, int);
LLNode * dequeue(QueueLL *);
LLNode * peek(QueueLL *);
int is_empty(QueueLL *);


int main(void) {
    QueueLL *queue = create_queue();
    LLNode *x;

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    while( !is_empty(queue) ) {
        x = dequeue(queue);
        printf("%d\n", x->data);

        // deallocate
        free(x);
    }

    enqueue(queue, 40);

    while( !is_empty(queue) ) {
        x = dequeue(queue);
        printf("%d\n", x->data);

        // deallocate
        free(x);
    }

    destroy_queue(queue);

    return 0;
}


// function definitions
QueueLL * create_queue() {
    // dynamically allocate the queue
    QueueLL *queue = malloc(sizeof(QueueLL));

    // set the top to NULL
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void destroy_queue(QueueLL *queue) {
    // deallocate the queue itself
    free(queue);
}


void enqueue(QueueLL *queue, int val) {
    // this is a copy of the linked list
    // add to tail code (with changed variable names)
    // take note that the two scenarios were combined here

    // create a new node
    LLNode *tmp = malloc(sizeof(LLNode));
    // set the data and the next components
    tmp->data = val;
    // because it is the new last element (no node after this)
    tmp->next = NULL;


    if( is_empty(queue) ) {
        // update the old last node so that it now knows
        // that it has a node after it (tmp)
        queue->front = tmp;
    }
    else {
        // the list will have a new tail
        queue->rear->next = tmp;
    }

    // update the rear of the list
    // to be the newly created node
    queue->rear = tmp;
}


LLNode * dequeue(QueueLL *queue) {
    // this is a copy of the linked list
    // remove head code (with changed variable names)

    // check if the list is empty
    if( is_empty(queue) ) {
        return NULL;
    }

    // create a temporary pointer to the
    // current head node because this will
    // be removed from the list shortly
    // and we want to keep reference
    LLNode *tmp = queue->front;

    // check if the current rear is also
    // the same front of the queue
    // this means that there is only one
    // node in the queue, therefore
    // after the dequeue, there will be
    // no node left (no rear)
    if(queue->front == queue->rear) {
        queue->rear = NULL;
    }

    // update the head so that the new head
    // is the next to the current head
    queue->front = queue->front->next;

    // probably do some cleanup?
    tmp->next = NULL;

    // return the reference to the old head
    return tmp;
}


LLNode * peek(QueueLL *queue) {
    // return a pointer to the front node
    return queue->front;
}


int is_empty(QueueLL *queue) {
    // check if the front node is
    // currently a NULL
    return queue->front == NULL;
}
