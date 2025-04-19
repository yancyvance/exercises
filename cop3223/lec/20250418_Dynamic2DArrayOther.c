#include <stdio.h>
#include <stdlib.h>

int main(void) {
    double *arr;
    int rows, cols;

    // ask for the dimension of this 2D array of double
    printf("How Many Rows: ");
    scanf("%d", &rows);

    printf("How Many Columns: ");
    scanf("%d", &cols);

    // Part 1: Allocating the 2D Array

    // allocate a single block of memory capable
    // of storing rows * cols elements
    arr = malloc(sizeof(double) * rows * cols);


    // Part 2: Processing the 2D Array

    // try to populate all the elements of the "2D array"
    // but again, it is just a 1D array
    // we do this mathematically
    double count = 0.0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            //arr[i*cols+j] = count++;                       // Approach 1: array bracket notation
            *(arr+(i*cols+j)) = count++;                     // Approach 2: pointer arithmetic notation
        }
    }

    // print the values of all the elements
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            //printf("%lf ", arr[i*cols+j]);                 // Approach 1: array bracket notation
            printf("%lf ", *(arr+(i*cols+j)) );              // Approach 2: pointer arithmetic notation
        }
        printf("\n");
    }


    // Part 3: Deallocating the 2D Array

    // deallocate the array
    free(arr);

    return 0;
}
