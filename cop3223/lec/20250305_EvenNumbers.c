#include <stdio.h>
#define MAX_SIZE 1000

// function prototypes
int is_even(int num);
int get_sum_even(int arr[MAX_SIZE], int count);
int get_max_even(int arr[MAX_SIZE], int count);


int main(void) {
    int N;
    int nums[MAX_SIZE];

    // Task 1: Get N from the user
    printf("Enter N: ");
    scanf("%d", &N);


    // Task 2: Ask the user to enter N numbers
    // and store them in an array
    for(int i = 0; i < N; i++) {
        printf("Enter #%d: ", i+1);
        scanf("%d", &nums[i]);
    }


    // Task 3: Get the sum of all even numbers
    // from the list of numbers entered by the user
    int sum_of_even = get_sum_even(nums, N);


    // Task 4: Find the highest even number
    // from the list of numbers entered by the user
    int max_even = get_max_even(nums, N);


    // Task 5: Display the final results
    printf("Sum of Even: %d\n", sum_of_even);
    printf("Max Even: %d\n", max_even);


    return 0;
}


// function definitions
int is_even(int num) {
    // shorter version
    return num % 2 == 0;

    /*
    // longer version
    if(num % 2 == 0) {
        return 1;
    }
    else {
        return 0;
    }
    */
}


int get_sum_even(int arr[MAX_SIZE], int count) {
    // This function will accept two parameters.
    // The first is an array of integers while the
    // second is an integer corresponding to the
    // number of numbers currently stored in the
    // array (which is passed as the first parameter).
    // It then returns the sum of all even numbers
    // stored in the array.

    // accumulator
    int sum = 0;

    // loop through each element of this array
    // and simply add to the accumulator
    // all the even numbers encountered so far
    for(int i = 0; i < count; i++) {
        // we want to check if this current
        // number is an even number or not
        if( is_even(arr[i]) ) {
            sum = sum + arr[i];
        }
    }

    // return the sum of all the
    // even numbers from the array
    return sum;
}


int get_max_even(int arr[MAX_SIZE], int count) {
    // This function will accept two parameters.
    // The first is an array of integers while the
    // second is an integer corresponding to the
    // number of numbers currently stored in the
    // array (which is passed as the first parameter).
    // It then returns the maximum even number
    // found in the array.

    // Note: There is a logic error here!

    // assume that the first element is the max even
    // note: it is possible for this to be an
    // incorrect assumption
    // for this problem, it is fine because eventually
    // we will correct this
    int max_idx = 0;

    // check through all the other elements
    for(int i = 1; i < count; i++) {
        // check if the current number is higher
        // than my assumed max
        if(arr[i] > arr[max_idx]) {
            // check further if the current number
            // is an even number
            if( is_even(arr[i]) ) {
                // update assumption
                max_idx = i;
            }
        }
    }

    // return the value at that location
    return arr[max_idx];
}
