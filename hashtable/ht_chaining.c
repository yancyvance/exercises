#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sample C Implementation of a hash table (chaining).
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-30.


typedef struct LLNode_s {
    char *data;
    struct LLNode_s *next;
} LLNode;

typedef struct LList_s {
    LLNode *head;
    LLNode *tail;
} LList;

typedef struct HashTable_s {
    // we have a pointer to pointers
    LList **table;
    int capacity;
} HashTable;



// function prototypes
HashTable * create_hash_table(int);
void destroy_hash_table(HashTable *);
LLNode * create_node(char *);
void destroy_node(LLNode *);
LList * create_linked_list();
void destroy_linked_list(LList *);
void destory_linked_list_recursive(LLNode *);
void add_to_tail(LList *, char *);
int hash_function(HashTable *, char *);
void insert(HashTable *, char *);
LLNode * search_table(HashTable *, char *);
LLNode * linked_list_search(LList *, char *);



int main(void) {
    // dynamically allocate the table
    HashTable *hash_table = create_hash_table(10);

    // insert the following data
    insert(hash_table, "bob");
    insert(hash_table, "bbo");


    // do a lookup on the table
    LLNode *tmp;
    tmp = search_table(hash_table, "boo");

    // check if this exists in the table
    if(tmp)
        printf("Found Node!\n");


    // deallocate the table
    destroy_hash_table(hash_table);

    return 0;
}



HashTable * create_hash_table(int capacity) {
    // dynamically allocate this array of
    // pointers to LLNodes given capacity
    HashTable *hash_table = malloc(sizeof(HashTable));

    // dynamically allocate this array of pointers to LLNode
    hash_table->table = malloc(sizeof(LList*) * capacity);

    // set all the pointers to NULL
    // to prevent from dealing with garbage values
    for(int i = 0; i < capacity; i++)
        hash_table->table[i] = NULL;

    hash_table->capacity = capacity;

    return hash_table;
}


void destroy_hash_table(HashTable *hash_table) {
    // traverse through each of the elements
    // of the dynamic array, and individually
    // destroy the linked list
    for(int i = 0; i < hash_table->capacity; i++) {
        // check if there is a linked list existing
        // at this location
        if(hash_table->table[i] != NULL)
            destory_linked_list_recursive(hash_table->table[i]->head);
    }

    // destroy the hash table itself
    free(hash_table);
}


LLNode * create_node(char *str) {
    // dynamically create a node
    LLNode *node = malloc(sizeof(LLNode));

    // set the appropriate attributes
    // dynamically allocate for the string
    // note that we add plus 1 due to the NULL
    // terminator for the string
    node->data = malloc(sizeof(char) * (strlen(str)+1));
    // we then copy the value of the str argument
    strcpy(node->data, str);

    // set the next to NULL
    node->next = NULL;

    return node;
}


void destroy_node(LLNode *node) {
    // deallocate the string first
    free(node->data);

    // deallocate the node itself
    free(node);
}


LList * create_linked_list() {
    // dynamically allocate one
    LList *list = malloc(sizeof(LList));

    // initialize the members
    list->head = NULL;
    list->tail = NULL;

    return list;
}


void destroy_linked_list(LList *list) {
    // if the linked list is not empty
    // traverse until the tail is reached
    // this is a wrapper function to the
    // recursive solution
    destory_linked_list_recursive(list->head);
}


void destory_linked_list_recursive(LLNode *node) {
    // this is a recursive function that
    // deallocates the nodes of a linked
    // list from the tail going back to
    // the head of the list
    // base case is if there is no more
    // node to visit
    if(node == NULL)
        return;

    // visit the next node
    destory_linked_list_recursive(node->next);

    // deallocate the node
    // think: it is like the postorder traversal
    // of a tree if you come to think of it
    // the call above is the L or R
    // the code below this is the V
    free(node);
}


void add_to_tail(LList *list, char *val) {
    // if linked list is empty, then set
    // the head and tail
    if(list->head == NULL) {
        list->head = list->tail = create_node(val);
        return;
    }

    // otherwise, simply add a new to the tail
    // create a temp node
    LLNode *tmp = create_node(val);
    list->tail->next = tmp;
    // update to have a new tail
    list->tail = tmp;
}


int hash_function(HashTable *hash_table, char *str) {
    // the following is a simple hash function
    // that gets the sum of the ascii of the
    // characters in str; it then maps
    // the sum to a corresponding number in the
    // range of 0 to size of hash table, inclusive
    // this is done through modulo operator
    int sum_of_ascii = 0;

    // we simply get the sum of the lowercase
    // version of all the letters of str
    int len = strlen(str);
    for(int i = 0; i < len; i++)
        sum_of_ascii = sum_of_ascii + str[i];

    // afterward, we do a division to the sum
    // so that the result will be in the range
    // of 0-capacity of the hash table
    return sum_of_ascii % hash_table->capacity;
}


void insert(HashTable *hash_table, char *str) {
    // hash the given string
    int hash_value = hash_function(hash_table, str);

    // check first if there is already a linked
    // list existing in this location, if none
    // create an empty one
    if( hash_table->table[hash_value] == NULL )
        hash_table->table[hash_value] = create_linked_list();

    // add to tail at the hash_value's location
    add_to_tail( hash_table->table[hash_value], str );
}


LLNode * search_table(HashTable *hash_table, char *str) {
    // this function searches a hash table
    // hash the given string
    int hash_value = hash_function(hash_table, str);

    // check if there is a list first
    if(hash_table->table[hash_value] != NULL) {
        // do a search operation on a linked list
        return linked_list_search(hash_table->table[hash_value], str);
    }

    // it is not found
    return NULL;
}


LLNode * linked_list_search(LList *list, char *str) {
    // check if the list is empty or not
    if(list->head == NULL)
        return NULL;

    LLNode *ptr = list->head;
    while(ptr != NULL) {
        // if this node has data
        // that we are looking for
        // we are dealing with a string
        if( strcmp(ptr->data, str) == 0 )
            return ptr;

        // go to the next
        ptr = ptr->next;
    }

    return NULL;
}
