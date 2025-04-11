#include <stdio.h>
#include <string.h>
#define MAX_WORD_SIZE 101
#define MAX_PEOPLE 10
#define INPUT_FILE "people.txt"

// define a structure
typedef struct Person_s {
    char name[MAX_WORD_SIZE];
    int age;
} Person;

// function prototypes
int find_max(Person people[], int size);
void introduce(Person p);
Person create_person(char n[], int a);
void inc(Person *p);
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

    // temporary storage holding the name
    // and age of a single person being
    // currently being processed
    char name[MAX_WORD_SIZE];
    int age;

    // declare an array of persons
    Person persons[MAX_PEOPLE];

    // read the N person information from the file
    for(int i = 0; i < N; i++) {
        // a way to check if we are correctly
        // processing the correct person
        //printf("Person %d\n", i+1);

        // read the name
        fgets(name, MAX_WORD_SIZE, ifile);

        // trim the name due to fgets
        trim_string(name);

        // read the age which is just a number
        fscanf(ifile, "%d", &age);

        // clear the buffer
        clear_buffer_file(ifile);

        // create a person and store it in
        // the array
        persons[i] = create_person(name, age);
    }

    // close the file
    fclose(ifile);


    // Part 1
    // find the oldest age by calling a helper
    // function we have defined in one of our
    // lectures on the topic of arrays
    int idx = find_max(persons, N);

    // print the result, we use the index
    // of the max age and access the name
    // of that person
    printf("%s %d\n", persons[idx].name, persons[idx].age);


    // Test: Have Everyone Introduce!
    printf("Before:\n");
    for(int i = 0; i < N; i++) {
        introduce( persons[i] );
    }

    // Test: Have Everyone's age increment
    for(int i = 0; i < N; i++) {
        // update age by pass-by-reference
        inc(&persons[i]);
    }

    // Test: Have Everyone Introduce!
    printf("After:\n");
    for(int i = 0; i < N; i++) {
        introduce( persons[i] );
    }


    // Part 2
    // Insert your code here




    return 0;
}


int find_max(Person people[], int size) {
    // this function simply returns the index of
    // the person with the maximum age assuming
    // all ages are distinct

    // we assume that the first person
    // is the max element
    int max_idx = 0;
    for(int i = 1; i < size; i++) {
        // if the person's age at this location turns
        // out to be lower than the current max
        if(people[i].age > people[max_idx].age) {
            // we update our tracker
            max_idx = i;
        }
    }

    // return the index of the max element
    return max_idx;
}


void introduce(Person p) {
    printf("Hi, I'm %s. I'm %d years old.\n", p.name, p.age);
}


Person create_person(char n[], int a) {
    // this is a function that creates a
    // Person and sets the values of the fields
    // based on the arguments received;
    // it also validates the age of the person

    // create a person
    Person tmp;

    // set the name of this person
    strcpy(tmp.name, n);

    // check if it is a valid age
    // where age is 0-1000 (inclusive)
    // otherwise, set to default of 0
    if(a < 0 || a > 1000) {
        a = 0;
    }

    // set the age of this person
    tmp.age = a;

    // return this newly created person
    return tmp;
}


void inc(Person *p) {
    // this function accepts are pointer to a
    // person struct; it should increment the
    // age of this person

    //(*p).age = (*p).age + 1;      // this is a long version
    p->age = p->age + 1;            // this is the same as the one above (shorter)

    //*p.age = *p.age + 1;          // this is wrong!
}


void clear_buffer_file(FILE *ifile) {
    // helper function that clear's the file buffer
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
