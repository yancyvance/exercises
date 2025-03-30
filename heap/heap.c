#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Sample C Implementation of heapsort.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-29.


typedef struct MinHeap_s {
    int *array;
    int capacity;
    int size;
} MinHeap;


// function prototypes
int get_left_index(int);
int get_right_index(int);
int get_parent_index(int);
void swap(int *, int *);
MinHeap * create_heap(int);
void destroy_heap(MinHeap *);
void heapify(MinHeap *, int);
void heapify_up(MinHeap *, int);
void insert(MinHeap *, int);
int extract_min(MinHeap *);
int peek(MinHeap *);
void decrease_key(MinHeap *, int, int);
int is_empty(MinHeap *);
void print_heap(MinHeap *);


int main(void) {
    // build an empty heap
    MinHeap *heap = create_heap(10);

    print_heap(heap);

    // add the following values
    insert(heap, 50);
    insert(heap, 40);
    insert(heap, 30);
    insert(heap, 20);
    insert(heap, 10);

    // confirm changes
    print_heap(heap);

    // peek
    printf("%d\n", peek(heap));

    // adjust the key of last node
    // to a lower one
    decrease_key(heap, heap->size-1, 5);

    // individually extract the min
    // until the heap becomes empty
    while( !is_empty(heap) ) {
        // extract the min
        int min_val = extract_min(heap);

        printf("%d\n", min_val);
    }

    // deallocate the heap
    destroy_heap(heap);

    return 0;
}


// function definitions
int get_left_index(int idx) {
    // assumption: index of first node
    // of the heap is 0
    return idx * 2 + 1;
}


int get_right_index(int idx) {
    // assumption: index of first node
    // of the heap is 0
    return idx * 2 + 2;
}


int get_parent_index(int idx) {
    // assumption: index of first node
    // of the heap is 0
    // the following does an integer division
    return (idx-1) / 2;
}


void swap(int *a, int *b) {
    // pass by reference type of swap
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


MinHeap * create_heap(int capacity) {
    // dynamically allocate a min heap
    MinHeap *heap = malloc(sizeof(MinHeap));

    // create an empty array
    heap->array = malloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;

    return heap;
}


void destroy_heap(MinHeap *heap) {
    // destroy the array first
    free(heap->array);

    // destroy the heap
    free(heap);
}


void heapify(MinHeap *heap, int idx) {
    // get the left and right indices
    int idx_left = get_left_index(idx);
    int idx_right = get_right_index(idx);
    int min_idx = idx;

    // find the minimum among the 3 nodes:
    // current node, left node, right node
    // the first part of the condition simply
    // checks if this computed child index
    // is within size to be valid (otherwise, invalid)
    if(idx_left < heap->size && heap->array[idx_left] < heap->array[min_idx])
        min_idx = idx_left;

    if(idx_right < heap->size && heap->array[idx_right] < heap->array[min_idx])
        min_idx = idx_right;

    // if the minimum turns out to be a child
    // do a swap and heapify at the new location
    if(min_idx != idx) {
        // swap
        swap(&(heap->array[min_idx]), &(heap->array[idx]));

        // do the same at the new heap location
        heapify(heap, min_idx);
    }
}


void heapify_up(MinHeap *heap, int idx) {
    // get the parent index
    int idx_parent = get_parent_index(idx);

    // find the minimum between the 2 nodes:
    // current node and its parent
    // the first part of the condition simply
    // checks if this computed parent index
    // is valid or non-negative (otherwise, invalid)
    if(idx_parent >= 0 && heap->array[idx] < heap->array[idx_parent]) {
        // swap
        swap(&(heap->array[idx]), &(heap->array[idx_parent]));

        // do the same at the new heap location
        heapify_up(heap, idx_parent);

    }
}


void insert(MinHeap *heap, int val) {
    // insert at the last available slot
    if(heap->size < heap->capacity) {
        // put at the last slot
        heap->array[heap->size++] = val;

        // do a heapify up at this location
        heapify_up(heap, heap->size-1);
    }
}


int extract_min(MinHeap *heap) {
    if( !is_empty(heap) ) {
        // if there is only a single one, then
        // return the root
        if(heap->size == 1)
            return heap->array[--heap->size];
        else {
            // if there are more than one,
            // temporarily hold the root then
            int tmp = heap->array[0];

            // copy the last element of the
            // heap and put it to the root
            // decrement the size as well
            heap->array[0] = heap->array[--heap->size];

            // heapify at the root to fix
            // any modifications due to this
            heapify(heap, 0);

            // return the old root value
            return tmp;
        }
    }

    // just return a very large number
    return INT_MAX;
}


int peek(MinHeap *heap) {
    if( !is_empty(heap) )
        return heap->array[0];

    // just return a very large number
    return INT_MAX;
}


void decrease_key(MinHeap *heap, int idx, int val) {
    // check first if this is a valid
    // index in the heap based on the size
    if(idx < heap->size) {
        // update the key of idx
        heap->array[idx] = val;

        // do a heapify up to fix
        // possible violations
        heapify_up(heap, idx);
    }
}


int is_empty(MinHeap *heap) {
    return heap->size == 0;
}


void print_heap(MinHeap *heap) {
    if(heap->size == 0) {
        printf("Heap is Empty.\n");
        return;
    }

    // helper function to simply print
    for(int i = 0; i < heap->size; i++)
        printf("%d ", heap->array[i]);
    printf("\n");
}
