#include <stdio.h>
#include <stdlib.h>

int main(void) {
    double **arr;
    int rows, cols;

    // ask for the dimension of this 2D array of double
    printf("How Many Rows: ");
    scanf("%d", &rows);

    printf("How Many Columns: ");
    scanf("%d", &cols);

    // Part 1: Allocating the 2D Array

    // allocate array with rows elements (rows)
    arr = malloc(sizeof(double*) * rows);

    // allocate an array with cols elements for each row
    for(int i = 0; i < rows; i++) {
        arr[i] = malloc(sizeof(double) * cols);
    }


    // Part 2: Processing the 2D Array

    // try to populate all the elements of the 2d array
    double count = 0.0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            //arr[i][j] = count++;                 // Approach 1: array bracket notation
            *((*(arr+i))+j) = count++;             // Approach 2: pointer arithmetic notation
        }
    }

    // print the values of all the elements
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            //printf("%lf ", arr[i][j]);           // Approach 1: array bracket notation
            printf("%lf ", *((*(arr+i))+j));       // Approach 2: pointer arithmetic notation
        }
        printf("\n");
    }


    // Part 3: Deallocating the 2D Array

    // deallocate array of each row
    for(int i = 0; i < rows; i++) {
        //free( &arr[i] );                         // Approach 1: array bracket notation
        free( arr+i );                             // Approach 2: pointer arithmetic notation
    }

    // deallocate the main array
    free(arr);

    return 0;
}
