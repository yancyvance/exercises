#include <stdio.h>
#define MAX_SIZE 100

// function prototype
void print_numbers(int arr[MAX_SIZE], int count);
void reset_array(int arr[MAX_SIZE], int count);
void reset_array_v2(int *arr, int count);

int main(void) {
    int nums[MAX_SIZE];
    int count;

    printf("Enter How Many Numbers: ");
    scanf("%d", &count);

    // we want to read the count numbers
    // from the user
    for(int i = 0; i < count; i++) {
        scanf("%d", &nums[i]);
    }

    // check if values were stored
    print_numbers(nums, count);

    // reset 0?
    //reset_array(nums, count);
    reset_array_v2(nums, count);

    // confirm if the numbers were reset
    print_numbers(nums, count);


    return 0;
}

void print_numbers(int arr[MAX_SIZE], int count) {
    for(int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void reset_array(int arr[MAX_SIZE], int count) {
    // this is a safer approach because you
    // are guaranteed that arr will be an array
    for(int i = 0; i < count; i++) {
        arr[i] = 0;
    }
}

void reset_array_v2(int *arr, int count) {
    // be careful because the assumption here
    // is that arr will receive an address
    // of an array; what if it is not an array?
    for(int i = 0; i < count; i++) {
        arr[i] = 0;
    }
}
