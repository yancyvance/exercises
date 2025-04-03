#include <stdio.h>
#include <string.h>
#define MAX_WORD_SIZE 101

// function prototype
int begins_with_vowel(char word[]);


int main(void) {
    // Task 1: How to store the word
    char word[MAX_WORD_SIZE];
    // this will hold our output string (pig latin)
    char output[MAX_WORD_SIZE+3];

    // Task 2: Obtain the word from the user
    printf("Enter Word: ");
    scanf("%s", word);

    // Task 3: Convert word to pig latin
    // check if it begins with vowel
    if( begins_with_vowel(word) ) {
        // if it begins with a vowel
        // simply add way at the end
        // of the word
        strcpy(output, word);
        strcat(output, "way");
    }
    else {
        // if it begins with a consonant
        // move the first letter at the end
        // and add ay at the end
        // of the word
        strcpy(output, &word[1]);
        strncat(output, word, 1);
        strcat(output, "ay");
    }

    // Task 4: Print the converted word
    printf("Pig Latin: %s", output);

    return 0;
}


int begins_with_vowel(char word[]) {
    // helper function to check if a string
    // begins with a vowel
    char alpha = word[0];
    return alpha == 'a' || alpha == 'e' || alpha == 'i' || alpha == 'o' || alpha == 'u';
}
