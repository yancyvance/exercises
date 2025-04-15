#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 256
#define GRADE_COUNT 3
#define INPUT_FILE_NAME "students.txt"

// COP 3223C Spring 2025
// Student Name: TODO_your_name_here
// File Name: pa6_yoursurname.c
// Note: Rename to use your actual surname. File name should be in lowercase.
// You must remove any whitespaces or dashes from your surname.
// Note: **do not** modify or remove TODO comments

typedef struct Student_s {
    char name[MAX_SIZE];
    double grades[GRADE_COUNT];
} Student;


// DO NOT MODIFY THIS PORTION
// function prototypes
void set_student(Student *p, char name[], double g1, double g2, double g3);
double compute_average(Student *p);
void introduce(Student *p);
Student * create_student();
void destroy_student(Student *p);
void clear_buffer_file(FILE *ifile);
void trim_string(char str[]);



// DO NOT MODIFY THIS PORTION OF THE MAIN FUNCTION
int main(void) {
    FILE *ifile;

    // open the input file for reading
    ifile = fopen(INPUT_FILE_NAME, "r");

    // check if the file was read successfully
    if(ifile == NULL) {
        // if there was a problem, simply return a 1
        // and terminate the program
        printf("Error. Cannot read file.");
        return 1;
    }

    // read how many students to process
    int N;
    fscanf(ifile, "%d", &N);

    // clear the buffer
    clear_buffer_file(ifile);

    // we dynamically allocate the array
    // with the size of N; this is a dynamic array
    // of pointers to a struct (student)
    Student **arr = malloc(sizeof(Student*) * N);

    // this is a temporary string placeholder
    char name[MAX_SIZE];
    double g1, g2, g3;

    // process the N students
    for(int i = 0; i < N; i++) {
        // first line will be a string for the name
        fgets(name, MAX_SIZE, ifile);

        // trim the string
        trim_string(name);

        // afterward, 3 grades follow
        fscanf(ifile, "%lf%lf%lf", &g1, &g2, &g3);

        // clear the buffer
        clear_buffer_file(ifile);

        // dynamically allocate a student at this
        // location (element)
        arr[i] = create_student();

        // set the attributes of this student
        set_student(arr[i], name, g1, g2, g3);

        // have this student introduce
        introduce(arr[i]);
    }

    // deallocate the students
    for(int i = 0; i < N; i++) {
        destroy_student(arr[i]);
    }

    // deallocate the dynamic array
    free(arr);


    return 0;
}
// END DO NOT MODIFY THIS PORTION OF THE MAIN FUNCTION



void set_student(Student *p, char name[], double g1, double g2, double g3) {
    // TODO 1 START
    // TODO 1: This function takes a pointer to a Student, a string (the student's name),
    // and three floating-point numbers representing the student's grades.
    // It assigns the name and grades to the corresponding fields in the Student struct.
    // The grades must be stored in the grades array in the order received:
    // g1 at index 0, g2 at index 1, and g3 at index 2.





    // TODO 1 END
}


double compute_average(Student *p) {
    // TODO 2 START
    // TODO 2: This function takes a pointer to a Student
    // and returns the average of the student's three grades.





    // TODO 2 END
}


void introduce(Student *p) {
    // TODO 3 START
    // TODO 3: This function takes a pointer to a Student and prints the student's name
    // followed by their average grade on a single line in the format: [name] [average].
    // The average must be displayed with exactly two decimal places, using standard rounding rules.
    // To receive credit, make sure to call the compute_average() function within this function.





    // TODO 3 END
}


Student * create_student() {
    // this is a helper function that
    // dynamically allocate a student
    return malloc(sizeof(Student));
}


void destroy_student(Student *p) {
    // this is a helper function that
    // frees the dynamically allocated memory
    // for a student
    free(p);
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
