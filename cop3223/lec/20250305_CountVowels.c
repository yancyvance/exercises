#include <stdio.h>
#include <ctype.h>

// function prototype
int count_vowels(char start, char end);

int main(void) {
    // the following are test codes to confirm
    // if our solution is correct or not
    //printf("%d\n", count_vowels('f', 'Y'));
    //printf("%d\n", count_vowels('y', 'b'));
    printf("%d\n", count_vowels('b', 'y'));

    return 0;
}

int count_vowels(char start, char end) {
    // clean the start and end values
    // change them to upper case
    start = toupper(start);
    end = toupper(end);

    // the ideal case is that start <= end
    // we have to check if it is not the ideal case
    // basically !(start <= end) which translates to
    // start > end
    // note: the order of the variables below does
    // not really matter
    if(end < start) {
        // we do a swap, we want to swap
        // the values of the two variables
        // this would require us to use
        // a third (temporary) variable
        // to hold the value of one of the
        // two variables
        int tmp = start;
        start = end;
        end = tmp;
    }

    // accumulator
    int vowel_count = 0;

    // run from start to end (letters)
    for(char letter = start; letter <= end; letter++) {
        // check if a letter is a vowel
        if(letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U') {
            //printf("%c\n", letter);

            // keep track how many vowels seen
            vowel_count++;
        }
    }

    // return the number of vowels found
    return vowel_count;
}
