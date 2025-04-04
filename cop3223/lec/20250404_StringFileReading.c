#include <stdio.h>
#define MAX_SIZE 255
#define FILE_NAME "words.txt"

/*
Sample Content for numbers.txt:
Hello World
How Are You
*/

// function prototypes
void clear_buffer(void);
void trim_string(char str[]);


int main(void) {
    char word[MAX_SIZE];
    FILE *ifile;

    // open the file for reading
    ifile = fopen(FILE_NAME, "r");

    if(ifile == NULL) {
        printf("Error. Unable to read file.\n");
        return 1;
    }

    // read strings that may contain whitespace
    while( fgets(word, MAX_SIZE, ifile) != NULL ) {
        // remove the extra newline
        trim_string(word);

        // print the word that was just read
        printf("%s\n", word);
    }

    // close the file
    fclose(ifile);

    return 0;
}


void clear_buffer(void) {
    // helper function that clear's the buffer
    while( getchar() != '\n' );
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
