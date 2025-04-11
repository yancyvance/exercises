#include <stdio.h>
#include <string.h>

typedef struct Person_s {
    char name[256];
    int age;
} Person;


// function prototypes
void introduce_v1(Person p);
void introduce_v2(Person *ptr);
void introduce_v3(Person *ptr);


int main(void) {
    Person p;

    // set name and age
    strcpy(p.name, "John Doe");
    p.age = 25;

    // print how much memory (in bytes) are used
    printf("Size of Person: %d\n", sizeof(p));

    // pass by value
    introduce_v1(p);

    // pass by reference
    // we need to pass the address
    introduce_v2(&p);

    // pass by reference
    // we need to pass the address
    introduce_v3(&p);

    return 0;
}


void introduce_v1(Person p) {
    printf("Hi, I'm %s. I'm %d years old.\n", p.name, p.age);
    printf("\tSize of Received Person: %d\n", sizeof(p));
}


void introduce_v2(Person *ptr) {
    printf("Hi, I'm %s. I'm %d years old.\n", ptr->name, ptr->age);
    printf("\tSize of Received Person: %d\n", sizeof(ptr));
}


void introduce_v3(Person *ptr) {
    printf("Hi, I'm %s. I'm %d years old.\n", (*ptr).name, (*ptr).age);
    printf("\tSize of Received Person: %d\n", sizeof(ptr));
}
