#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_WORD_SIZE 100

// function prototypes
int count_vowels(char word[]);
int get_length(char word[]);


int main(void) {
    // Task 1: Find a way to store the single word
    char word[MAX_WORD_SIZE];

    // Task 2: Ask the user to enter a word
    printf("Enter Word: ");
    scanf("%s", word);

    // Task 3: Count the vowels in the word
    int count = count_vowels(word);

    // Task 4: Report how many vowels found
    printf("There are %d vowels in %s", count, word);

    return 0;
}


int count_vowels(char word[]) {
    // we simply want to traverse through the string
    // and count how many vowels we have seen
    int count = 0;
    //int len = get_length(word);   // we experimented this first
    int len = strlen(word);         // but ended using the built-in
    for(int i = 0; i < len; i++) {
        char alpha = tolower( word[i] );
        if(alpha == 'a' || alpha == 'e' || alpha == 'i' || alpha == 'o' || alpha == 'u') {
            count++;
        }
    }
    return count;
}


int get_length(char word[]) {
    // this is a helper function that returns
    // how many characters are there in the
    // array of chars that are to the left
    // of the \0 char; in short, the length
    // of the string
    int count = 0;

    for(int i = 0; ; i++) {
        if( word[i] == '\0' ) {
            break;
        }
        count++;
    }

    return count;
}
