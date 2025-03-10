#include <stdio.h>
#include <stdlib.h>

// Sample C Implementation of a Singly Linked List.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-02-24.

typedef struct LLNode_s {
    int data;
    struct LLNode_s *next;
} LLNode;
/*
typedef struct LLNode_s {
    LLNode *head;
} LLNode;
*/

// function prototypes
int is_empty(LLNode *);
int get_size(LLNode *);
void traverse_list_existing_list(LLNode *);
void traverse_list_empty_list(LLNode *);
void traverse_list(LLNode *);
void add_new_element_existing_list(LLNode **, int);
void add_new_element_empty_list(LLNode **, int);
void add_new_element(LLNode **, int);
LLNode * search_list(LLNode *, int );
LLNode * remove_element_existing_list_not_first_node(LLNode **, int);
LLNode * remove_element_existing_list_first_node(LLNode **, int);
LLNode * remove_element(LLNode **, int);
LLNode * get_element_at(LLNode *, int);
void insert_new_element_at_existing_list_non_zero_pos(LLNode **, int, int);
void insert_new_element_at_existing_list_zero_pos(LLNode **, int, int);
void insert_new_element_at(LLNode **, int, int);
void traverse_list_recursive(LLNode *);
void add_new_element_recursive(LLNode **, int);
LLNode * remove_element_recursive(LLNode **, int);
void add_to_head(LLNode **, int);
void add_to_tail(LLNode **, int);
LLNode * remove_head(LLNode **);
LLNode * remove_tail(LLNode **);


/*
    The primary functions you want to use are:
        int is_empty(LLNode *);
        int get_size(LLNode *);
        void traverse_list(LLNode *);
        void add_new_element(LLNode **, int);
        LLNode * search_list(LLNode *, int );
        LLNode * remove_element(LLNode **, int);
        LLNode * get_element_at(LLNode *, int);
        void insert_new_element_at(LLNode **, int, int);
        void add_to_head(LLNode **, int);
        void add_to_tail(LLNode **, int);
        LLNode * remove_head(LLNode **);
        LLNode * remove_tail(LLNode **);

    The other functions are helper functions that
    accounts for certain scenarios. The functions above
    call these helper functions based on the scenario.

    You can actually consolidate these helper functions
    into a single primary function. I intentionally
    chose this approach to demonstrate that certain
    operations behave differently based on the scenario.
*/


int main(void) {
    // dynamically allocate a linked list
    LLNode *head = malloc(sizeof(LLNode));

    // set the head to NULL
    // because the list is empty
    head = NULL;

    // check the list first
    traverse_list(head);


    // add a node via recursive approach
    add_new_element_recursive(&head, 200);

    // add nodes
    add_new_element(&head, 10);
    add_new_element(&head, 20);
    add_new_element(&head, 30);

    // add a node via recursive approach
    add_new_element_recursive(&head, 70);


    // check the list first
    traverse_list(head);


    LLNode *tmp = remove_element(&head, 30);

    // deallocate
    free(tmp);


    // check the list again
    traverse_list(head);


    // insert at a certain location
    insert_new_element_at(&head, 2, 90);


    // check the list again
    printf("Iterative Version:\n");
    traverse_list(head);

    printf("Recursive Version:\n");
    // try the recursive version
    traverse_list_recursive(head);


    // insert at a certain location
    insert_new_element_at(&head, 0, 100);


    // check the list again
    traverse_list(head);


    tmp = search_list(head, 100);

    if(tmp) {
        printf("Found 100!\n");
    }


    // deallocate all
    tmp = remove_element(&head, 10);
    free(tmp);

    // check the list again
    traverse_list(head);

    printf("Recursive Delete\n");
    //tmp = remove_element(list, 20);
    tmp = remove_element_recursive(&head, 20);
    free(tmp);

    // check the list again
    traverse_list(head);

    tmp = remove_element(&head, 90);
    free(tmp);

    // check the list again
    traverse_list(head);


    tmp = remove_element(&head, 100);
    free(tmp);

    // check the list again
    traverse_list(head);

    // insert at a certain location
    insert_new_element_at(&head, 0, 80);


    // check the list again
    traverse_list(head);


    tmp = remove_element(&head, 80);
    free(tmp);


    // check the list again
    traverse_list(head);


    tmp = remove_element_recursive(&head, 200);
    free(tmp);


    // check the list again
    traverse_list(head);



    tmp = remove_element_recursive(&head, 70);
    free(tmp);


    // check the list again
    traverse_list(head);


    add_to_head(&head, 10);
    add_to_head(&head, 20);
    add_to_head(&head, 30);

    // check the list again
    traverse_list(head);

    tmp = remove_tail(&head);
    free(tmp);

    // check the list again
    traverse_list(head);

    tmp = remove_tail(&head);
    free(tmp);

    // check the list again
    traverse_list(head);

    tmp = remove_tail(&head);
    free(tmp);

    // check the list again
    traverse_list(head);




    // deallocate the linked list
    free(head);


    return 0;
}



int is_empty(LLNode *head) {
    // check if there is a head node
    return head == NULL;
}


int get_size(LLNode *head) {
    // this function returns the number of
    // nodes in the linked list
    int count = 0;
    LLNode *ptr;
    ptr = head;

    while(ptr != NULL) {
        // increment the number of nodes seen so far
        count++;

        ptr = ptr->next;
    }

    // number of nodes seen
    return count;
}


void traverse_list_existing_list(LLNode *head) {
    // this function prints all the elements of the list
    LLNode *ptr;

    // set the pointer to the first node
    ptr = head;

    while(ptr != NULL) {
        printf("%d ", ptr->data);

        // update the pointer
        ptr = ptr->next;
    }

    printf("\n");
}


void traverse_list_empty_list(LLNode *head) {
    // this function prints all the elements of the list
    printf("The List is Empty!\n");
}


void traverse_list(LLNode *head) {
    if(is_empty(head)) {
        traverse_list_empty_list(head);
    }
    else {
        traverse_list_existing_list(head);
    }
}


void add_new_element_existing_list(LLNode **head, int val) {
    // this function adds an element at the end of the list
    // the parameter val is set as the data of the new node
    LLNode *ptr;

    // set the pointer to the first node
    ptr = *head;

    while(ptr->next != NULL) {
        // go to the last node
        // we want the scenario in which
        // ptr will eventually point to the
        // last element of the list since
        // we will use it shortly to connect
        // a newly created node
        ptr = ptr->next;
    }

    // create a new node
    LLNode *tmp = malloc(sizeof(LLNode));
    // set the data and the next components
    tmp->data = val;
    // because it is the new last element (no node after this)
    tmp->next = NULL;
    // update the old last node so that it now knows
    // that it has a node after it (tmp)
    ptr->next = tmp;
}


void add_new_element_empty_list(LLNode **head, int val) {
    // this function adds an element to an empty list
    // the parameter val is set as the data of the new node

    // create a new node
    LLNode *tmp = malloc(sizeof(LLNode));
    // set the data and the next components
    tmp->data = val;
    // because it is the new last element (no node after this)
    tmp->next = NULL;
    // update the old last node so that it now knows
    // that it has a node after it (tmp)
    *head = tmp;
}


void add_new_element(LLNode **head, int val) {
    // this is a function capable of determining which
    // scenario to deal with when adding a new element
    if(is_empty(*head)) {
        add_new_element_empty_list(head, val);
    }
    else {
        add_new_element_existing_list(head, val);
    }
}


LLNode * search_list(LLNode *head, int query) {
    // this function searches for query if it can be
    // found in the linked list

    LLNode *ptr;
    ptr = head;

    while(ptr != NULL) {
        // if this node currently has data
        // which is what you are looking for (query)
        if(ptr->data == query) {
            // return a reference to this LLNode
            return ptr;
        }

        ptr = ptr->next;
    }

    // if not in the list, return NULL
    return NULL;
}


LLNode * remove_element_existing_list_not_first_node(LLNode **head, int query) {
    // this function removes from the list the first node
    // that has the a data value the same as query
    // it then returns a pointer to this LLNode
    // instead of deallocating it here

    LLNode *ptr;
    ptr = *head;

    while(ptr->next != NULL) {
        if(ptr->next->data == query) {
            // temporarily remember the reference
            // to the node that will be removed
            // from the list; otherwise, we can't
            // reference to it anymore later
            LLNode *tmp = ptr->next;

            // update the node right before the node
            // you are about to remove
            // indicate that this node will have a new
            // node that comes after it after we
            // remove the node that has the query value
            ptr->next = ptr->next->next;

            // post-cleanup?
            tmp->next = NULL;

            // return a reference to this node
            // that we just removed
            return tmp;
        }

        ptr = ptr->next;
    }

    // if there is no node that has a data value
    // that we are looking for (query)
    return NULL;
}


LLNode * remove_element_existing_list_first_node(LLNode **head, int query) {
    // check if this lone node has data value
    // same with query
    if((*head)->data == query) {
        LLNode *tmp;
        tmp = *head;

        // to indicate that removing this node
        // will remove the current head, therefore
        // the list will have a new head
        *head = (*head)->next;

        // return a reference to this node
        return tmp;
    }


    // if this node's data value is not
    // what we are looking for (query)
    return NULL;
}


LLNode * remove_element(LLNode **head, int query) {
    // check if there is a list
    if(!is_empty(*head)) {
        // check if trying to delete the first node
        if((*head)->data == query) {
            // multiple elements
            return remove_element_existing_list_first_node(head, query);
        }
        else {
            // single element
            return remove_element_existing_list_not_first_node(head, query);
        }
    }

    // the list is empty, don't do anything
    return NULL;
}


LLNode * get_element_at(LLNode *head, int pos) {
    int i;
    LLNode *ptr;
    ptr = head;

    while(ptr != NULL) {
        if(i == pos) {
            return ptr;
        }

        // number of nodes seen so far
        i++;
        ptr = ptr->next;
    }

    // did not find any element
    return NULL;
}


void insert_new_element_at_existing_list_non_zero_pos(LLNode **head, int pos, int val) {
    LLNode *ptr;
    ptr = *head;
    // index variable
    int i = 0;

    while(ptr != NULL) {
        // if the next i will be the correct position
        // where to put the node, stop here
        // because we want ptr to point to the node
        // that comes before i+1 position
        // since we are updating that node's next
        // component to point to the newly created node
        if(i+1 == pos) {
            LLNode *tmp = malloc(sizeof(LLNode));
            tmp->data = val;
            tmp->next = ptr->next;
            ptr->next = tmp;

            return;
        }

        i++;
        ptr = ptr->next;
    }
}


void insert_new_element_at_existing_list_zero_pos(LLNode **head, int pos, int val) {
    // this new node will become the new head of the list
    LLNode *tmp = malloc(sizeof(LLNode));
    tmp->data = val;

    // next node of this new node will be whatever
    // used to be the head of the list
    // it can be an actual node OR NULL (empty list)
    tmp->next = *head;

    // list will have a new head
    *head = tmp;
}


void insert_new_element_at(LLNode **head, int pos, int val) {
    // check if pos is 0 or not
    if(pos == 0) {
        insert_new_element_at_existing_list_zero_pos(head, pos, val);
    }
    else {
        insert_new_element_at_existing_list_non_zero_pos(head, pos, val);
    }
}


void traverse_list_recursive(LLNode *ptr) {
    // if we are already pointing to a NULL
    // we have already reached the end of the list
    if(ptr == NULL) {
        // perhaps the new line?
        printf("\n");
        return;
    }

    // print the values
    printf("%d ", ptr->data);
    // recursive call to next node
    // essentially, traverse the node that
    // comes after the current node
    traverse_list_recursive(ptr->next);
}


void add_new_element_recursive(LLNode **ptr, int val) {
    // check first if this node is NULL
    // if it is, then it was because the list is empty
    if(*ptr == NULL) {
        // create a new node
        LLNode *tmp = malloc(sizeof(LLNode));
        // set the data and the next components
        tmp->data = val;
        // because it is the new last element (no node after this)
        tmp->next = NULL;
        // update the old last node so that it now knows
        // that it has a node after it (tmp)
        *ptr = tmp;

        return;
    }

    // otherwise, process and proceed until
    // the second to the last node is reached
    if((*ptr)->next != NULL) {
        // we pass the address of this node since
        // we want to update this
        add_new_element_recursive(&(*ptr)->next, val);
    }
    else {
        // if it is, then add the node then return
        // this is a base case

        // create a new node
        LLNode *tmp = malloc(sizeof(LLNode));
        // set the data and the next components
        tmp->data = val;
        // because it is the new last element (no node after this)
        tmp->next = NULL;
        // update the old last node so that it now knows
        // that it has a node after it (tmp)
        (*ptr)->next = tmp;
    }
}


LLNode * remove_element_recursive(LLNode **ptr, int query) {
    // check first if this node is NULL
    // if it is, then it was because the list is empty
    if(*ptr == NULL) {
        // this means the list is empty, return NULL
        return NULL;
    }
    else {
        // if we are looking for the head
        if((*ptr)->data == query) {
            LLNode *tmp;
            tmp = *ptr;

            // to indicate that removing this node
            // will remove the current head, therefore
            // the list will have a new head
            (*ptr) = (*ptr)->next;

            // return a reference to this node
            return tmp;
        }
    }

    // otherwise, process and proceed until
    // the second to the last node is reached
    if((*ptr)->next != NULL) {
        // check if this is what we want to delete
        if((*ptr)->next->data == query) {
            // use a temporary pointer to refer
            // to the node that will be removed
            LLNode *tmp = (*ptr)->next;

            // remove the node from the list and
            // update the links
            (*ptr)->next = (*ptr)->next->next;

            // simply just set the next pointer
            tmp->next = NULL;

            // return the node that was just removed
            return tmp;
        }

        // proceed and keep finding the element
        return remove_element_recursive(&(*ptr)->next, query);
    }

    return NULL;
}


void add_to_head(LLNode **head, int val) {
    // we reuse the insert_new_element_at() and specify
    // pos = 0
    insert_new_element_at(head, 0, val);
}


void add_to_tail(LLNode **head, int val) {
    // we reuse the add_new_element() because
    // this was the add to tail behavior
    add_new_element(head, val);
}


LLNode * remove_head(LLNode **head) {
    // check if the list is empty
    if( is_empty(*head) ) {
        return NULL;
    }

    // create a temporary pointer to the
    // current head node because this will
    // be removed from the list shortly
    // and we want to keep reference
    LLNode *tmp = *head;

    // update the head so that the new head
    // is the next to the current head
    *head = (*head)->next;

    // probably do some cleanup?
    tmp->next = NULL;

    // return the reference to the old head
    return tmp;
}


LLNode * remove_tail(LLNode **head) {
    // check if the list is empty
    if( is_empty(*head) ) {
        return NULL;
    }

    // check if there is only a single element
    if((*head)->next == NULL) {
        LLNode *tmp = *head;
        tmp->next = NULL;
        *head = NULL;
        return tmp;
    }

    // traverse up to the second to the last element
    LLNode *ptr = *head;
    while(ptr->next->next != NULL) {
        ptr = ptr->next;
    }

    // remove as usual since
    // ptr is now pointing at the
    // second to the last element
    LLNode *tmp = ptr->next;
    ptr->next = NULL;

    // cleanup perhaps?
    tmp->next = NULL;
    return tmp;
}
