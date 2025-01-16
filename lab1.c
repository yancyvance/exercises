#include <stdio.h>

// define the 3 structures here, namely cdate_t, ctime_t, and cdatetime_t
// TODO 1: complete the code




void display_datetime(cdatetime_t *dt) {
    /* This function prints out the entire details of dt using printf().
     * It follows the format: Month dd, yyyy HH:MM:SS (HH is in 24 hour format 0-23)
     * For example: January 01, 2025 13:05:45
     * For the month, it should display the complete month name
     * where the first letter is capitalized while the remaining
     * letters are in lower-case.
     * Separate the day and year by a comma.
     * For the day, hour, minute, and second components, display
     * a leading zero if there is only a single digit. For example:
     * 5 should be display as 05; but 15 should be display as 15.
     * Lastly, end with the newline character (\n).
    */

    // TODO 2: complete the code
}

int compare_datetimes(cdatetime_t *dt1, cdatetime_t *dt2) {
    /* This function compares two cdatetime_t pointers.
     * It determins which of the two comes first chronologically.
     * Return:
     *      -1 if dt1 precedes dt2
             1 if dt2 precedes dt1
             0 if dt1 and dt2 are the same
    */ 
    
    // TODO 3: complete the code



    return 0;
}

int main(void) {
    cdatetime_t dt1;
    cdatetime_t dt2;
    int entries_count;
    
    // ask the user how many lines or entries to process
    scanf("%d", &entries_count);

    for(int i = 0; i < entries_count; i++) {
        // Read the user input and assign them to their corresponding locations in the struct
        // Expect 12 ints for each line in the following order (month day year hour minute second) (month day year hour minute second).
        // The first 6 ints will be the information for dt1 while the next 6 ints will be the information for dt2.
        // You may assume that the user enters valid dates.
        
        // TODO 4: complete the code
        
        
        // ---- NOTE: DO NOT MODIFY ANY CODE AFTER THIS LINE! ----
        
        // call the comparison
        int result = compare_datetimes(&dt1, &dt2);

        if(result < 0) {
            // dt1 precedes dt2
            display_datetime(&dt1);
        }
        else if(result > 0) {
            // dt2 precedes dt1
            display_datetime(&dt2);
        }
        else {
            // it's a tie, so simply display dt1
            display_datetime(&dt1);
        }
    }

    return 0;
}
