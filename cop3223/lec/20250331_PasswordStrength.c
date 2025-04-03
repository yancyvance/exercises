#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD_SIZE 101

// function prototypes
int is_strong(char password[]);


int main(void) {
    // Task 1: How to store the password (string)
    char pword[MAX_WORD_SIZE];

    // Task 2: Obtain the password from the user
    printf("Enter Password: ");
    scanf("%s", pword);

    // Task 3: Check if password is strong or not
    int ret_value = is_strong(pword);

    // Task 4: Report if password is strong/weak
    if(ret_value) {
        printf("Password is Strong\n");
    }
    else {
        printf("Password is Weak\n");
    }

    return 0;
}


int is_strong(char password[]) {
    // this is a helper function that determines
    // whether a given function is strong or not
    // it returns either 1 or 0, respectively

    // A password is strong if it meets the following:
    // at least one lowercase letter, one uppercase letter,
    // one digit, and one of the following symbols (@ ! # $)
    int c_lower = 0;
    int c_upper = 0;
    int c_digit = 0;
    int c_symbol = 0;

    // inspect each character from beginning to end
    // therefore, we traverse through the array
    int len = strlen(password);
    for(int i = 0; i < len; i++) {
        int alpha = password[i];

        // is it lowercase? a-z
        if( alpha >= 'a' && alpha <= 'z' ) {
            c_lower++;
        }
        // is it uppercase? A-Z
        else if( isupper(alpha) ) {
            c_upper++;
        }
        // is it digit? '0'-'9'
        else if( isdigit(alpha) ) {
            c_digit++;
        }
        // is it special symbols? @ ! # $
        else if( alpha == '@' || alpha == '!' || alpha == '#' || alpha == '$' ) {
            c_symbol++;
        }
    }

    // all the requirements need to be satisfied
    return c_lower > 0 && c_upper > 0 && c_digit > 0 && c_symbol > 0;
}
