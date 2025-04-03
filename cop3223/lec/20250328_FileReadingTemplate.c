#include <stdio.h>
#define FILE_NAME "numbers.txt"

/*
Sample Content for numbers.txt:
10
20
30
40
50
*/

int main(void) {
    FILE *ifile;

    // Task 1: Open file in reading mode
    // because it is reading mode, it assumes
    // that this file is existing!
    ifile = fopen(FILE_NAME, "r");

    // (Optional) check the value of the FILE pointer
    // Don't forget to remove this as this
    // is an extra output; you just want to
    // know if your file was loaded properly.
    // You will see a non-zero value if it was succesful
    //printf("%p\n", ifile);

    // Task 2: Check if file was loaded correctly
    if(ifile == NULL) {
        // terminate the program because
        // the file needed cannot be found
        printf("Error. Unable to read file.\n");
        return 1;
    }

    // if successful, then the program should
    // reach this point

    // Task 3: TODO: process file
    // Example below is to read the file
    // which contains numbers and will
    // read all until the End Of File is reached
    // or in short, no more contents to read
    int num;
    while( fscanf(ifile, "%d", &num) != EOF ) {
        printf("%d\n", num);
    }

    // Task 4: Close the file
    fclose(ifile);

    return 0;
}
