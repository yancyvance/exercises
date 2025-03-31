#include <stdio.h>

// Sample C Implementation of heapsort.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-28.

// function prototypes
int get_left_index(int);
int get_right_index(int);
int get_parent_index(int);
void heapify(int *, int, int);
void swap(int *, int *);
void build_heap(int *, int);
void heapsort(int *, int);
void print_heap(int *, int);


int main(void) {
    int nums[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int size = sizeof(nums) / sizeof(int);

    // print the array
    print_heap(nums, size);

    // sort the array
    heapsort(nums, size);

    // print the heap
    print_heap(nums, size);

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


void heapify(int *arr, int size, int idx) {
    // get the left and right indices
    int idx_left = get_left_index(idx);
    int idx_right = get_right_index(idx);
    int min_idx = idx;

    // find the minimum among the 3 nodes:
    // current node, left node, right node
    // the first part of the condition simply
    // checks if this computed child index
    // is within size to be valid (otherwise, invalid)
    if(idx_left < size && arr[idx_left] < arr[min_idx])
        min_idx = idx_left;

    if(idx_right < size && arr[idx_right] < arr[min_idx])
        min_idx = idx_right;

    // if the minimum turns out to be a child
    // do a swap and heapify at the new location
    if(min_idx != idx) {
        // swap
        swap(&arr[min_idx], &arr[idx]);

        // do the same at the new heap location
        heapify(arr, size, min_idx);
    }
}


void swap(int *a, int *b) {
    // pass by reference type of swap
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void build_heap(int *arr, int size) {
    // find the last internal node
    int idx = get_parent_index(size-1);

    // find your way up to the root node
    // do this level-wise
    while(idx >= 0) {
        // for each node, do heapify
        heapify(arr, size, idx);

        idx--;
    }
}


void heapsort(int *arr, int size) {
    // build the heap
    build_heap(arr, size);

    // determine how many nodes are unsorted
    int count_unsorted = size;

    // while there are still nodes that
    // are unsorted, repeat the process
    while(count_unsorted > 1) {
        // swap
        swap(&arr[0], &arr[count_unsorted-1]);

        // decrement count of unsorted nodes
        count_unsorted--;

        // heapify from the root
        heapify(arr, count_unsorted, 0);
    }

    // reverse the array to make
    // it ascending order
    for(int i = 0; i < size/2; i++) {
        swap(&arr[i], &arr[size-1-i]);
    }
}


void print_heap(int *arr, int size) {
    // helper function to simply print
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
