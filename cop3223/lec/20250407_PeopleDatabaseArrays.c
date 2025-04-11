#include <stdio.h>
#include <string.h>
#define MAX_WORD_SIZE 101
#define MAX_PEOPLE 10
#define INPUT_FILE "people.txt"
#define OUTPUT_FILE "older.txt"

// function prototypes
int find_max(int nums[], int size);
void clear_buffer_file(FILE *ifile);
void trim_string(char str[]);


int main(void) {
    // open the file for reading
    FILE *ifile = fopen(INPUT_FILE, "r");

    if(ifile == NULL) {
        printf("Error. Unable to read file.\n");
        return 1;
    }

    // read how many people will
    // be processed by the program
    int N;
    fscanf(ifile, "%d", &N);

    // clear the buffer
    clear_buffer_file(ifile);

    // store all the information in 2 parallel
    // arrays; one which is an array of string
    // and another which is an array of integers
    char names[MAX_PEOPLE][MAX_WORD_SIZE];
    int ages[MAX_PEOPLE];

    // read the N person information from the file
    for(int i = 0; i < N; i++) {
        // a way to check if we are correctly
        // processing the correct person
        //printf("Person %d\n", i+1);

        // read the name
        fgets(names[i], MAX_WORD_SIZE, ifile);

        // trim the name due to fgets
        trim_string(names[i]);

        // read the age which is just a number
        fscanf(ifile, "%d", &ages[i]);

        // clear the buffer
        clear_buffer_file(ifile);

        // print the information to confirm
        // if it was correctly stored
        //printf("%s %d\n", names[i], ages[i]);
    }

    // close the file
    fclose(ifile);


    // Part 1
    // find the oldest age by calling a helper
    // function we have defined in one of our
    // lectures on the topic of arrays
    int idx = find_max(ages, N);

    // print the result, we use the index
    // of the max age and access the name
    // of that person
    printf("%s %d\n", names[idx], ages[idx]);


    // Part 2
    // prepare the output file
    FILE *ofile = fopen(OUTPUT_FILE, "w");

    // write on the first line N, the
    // number of people to store
    fprintf(ofile, "%d\n", N);

    // then write the name and ages
    for(int i = 0; i < N; i++) {
        fprintf(ofile, "%s\n", names[i]);
        fprintf(ofile, "%d\n", ages[i]+1);
    }

    // close the file
    fclose(ofile);


    return 0;
}


int find_max(int nums[], int size) {
    // this function simply returns the index of
    // the maximum element assuming that all
    // elements are distinct

    // we assume that the first element
    // is the max element
    int max_idx = 0;
    for(int i = 1; i < size; i++) {
        // if the value at this location turns
        // out to be lower than the current max
        if(nums[i] > nums[max_idx]) {
            // we update our tracker
            max_idx = i;
        }
    }

    // return the index of the max element
    return max_idx;
}


void clear_buffer_file(FILE *ifile) {
    // helper function that clears the file buffer
    int c;
    while( (c = fgetc(ifile)) != '\n' && c != EOF );
}


void trim_string(char str[]) {
    // helper function that will remove the extra new line
    // begin at location right before
    // the null terminator of the string
    int len = strlen(str) - 1;

    // from the right, keep moving to the left;
    // continue doing so until what you see right
    // now is not a newline character anymore
    while(len > 0) {
        // stop moving to the left once you don't
        // see a newline character anymore
        if(str[len] != '\n' && str[len] != '\r')
            break;

        len--;
    }

    // len is currently pointing at the
    // last character right before a newline
    // therefore, it should be immediately
    // followed by the null character
    str[len+1] = '\0';
}
