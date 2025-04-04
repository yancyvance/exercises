#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define LETTER_COUNT 26

// Sample C Implementation of a trie.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-04-02.


typedef struct TrieNode_s {
    struct TrieNode_s *children[LETTER_COUNT];
    int is_terminal;
} TrieNode;

typedef struct Trie_s {
    TrieNode *root;
} Trie;


// function prototypes
Trie * create_trie();
TrieNode * create_node();
void destroy_trie(Trie *);
void destroy_node(TrieNode *);
int get_char_index(char);
char index_to_char(int);
void insert(Trie *, char *);
void remove_string(Trie *, char *);
int remove_string_recursive(TrieNode *, char *, int, int);
int search(Trie *, char *);
int has_children(TrieNode *);


int main(void) {
    // create a trie
    Trie *trie = create_trie();


    // insert the following strings
    insert(trie, "hello");
    insert(trie, "hi");
    insert(trie, "helios");
    insert(trie, "hope");
    insert(trie, "hopeful");
    insert(trie, "hopefully");

    // do a lookup
    printf("%d\n", search(trie, "hi"));
    printf("%d\n", search(trie, "hello"));
    printf("%d\n", search(trie, "hopeful"));

    // remove string
    remove_string(trie, "hopefully");

    // do a lookup
    printf("%d\n", search(trie, "hopeful"));
    printf("%d\n", search(trie, "hopefully"));


    // deallocate trie
    destroy_trie(trie);

    return 0;
}


Trie * create_trie() {
    // dynamically create a trie
    Trie *trie = malloc(sizeof(Trie));

    // dynamically allocate the root node
    trie->root = create_node();

    return trie;
}


TrieNode * create_node() {
    // dynamically create a new node
    TrieNode *node = malloc(sizeof(TrieNode));

    // set all children pointers to NULL
    for(int i = 0; i < LETTER_COUNT; i++) {
        node->children[i] = NULL;
    }

    // set the flag to false
    // indicating that this is not
    // a terminal node for a certain string
    node->is_terminal = 0;

    return node;
}


void destroy_trie(Trie *trie) {
    destroy_node(trie->root);

    // destroy the trie
    free(trie);
}


void destroy_node(TrieNode *node) {
    // this is a postorder traversal
    // visit all the children first
    // then visit the current node
    // base case
    if(node == NULL)
        return;

    // postorder visit all the children
    // and individually destroy them
    for(int i = 0; i < LETTER_COUNT; i++) {
        destroy_node(node->children[i]);
    }

    // deallocate this current node
    free(node);
}


int get_char_index(char alpha) {
    // change to lowercase first
    alpha = tolower(alpha);

    return alpha-'a';
}


char index_to_char(int idx) {
    // convert index to lowercase letter
    return (char) (idx+'a');
}


void insert(Trie *trie, char *str) {
    // create a pointer to the root
    TrieNode *ptr = trie->root;

    // traverse through each character
    // of the string
    int len = strlen(str);

    for(int i = 0; i < len; i++) {
        int idx = get_char_index(str[i]);

        // check if there is no existing
        // node for this letter
        if(ptr->children[idx] == NULL) {
            // create a new node for that
            // letter
            ptr->children[idx] = create_node();
        }

        // traverse to the next node
        ptr = ptr->children[idx];
    }

    // once we reached the last letter
    // ptr is pointing at the last node
    // therefore, set the flag of this
    // node to 1 or true
    ptr->is_terminal = 1;
}


void remove_string(Trie *trie, char *str) {
    // this is just a wrapper function
    // for the recursive function that
    // will be called to traverse the trie
    // one letter at a time
    remove_string_recursive(trie->root, str, strlen(str), 0);
}


int remove_string_recursive(TrieNode *node, char *str, int len, int pos) {
    // this recursive function returns 1 if
    // it deleted a node, 0 otherwise

    // if there is no node, return 0
    if(node == NULL)
        return 0;

    // base case, we have reached
    // the last letter
    if(len == pos) {
        // check first if the search was
        // successful by looking at whether
        // this node is a terminal node
        // if it is not, then safely terminate
        // the delete operation; search failed!
        if( !(node->is_terminal) )
            return 0;

        // check if this node about to be deleted
        // has children
        if( has_children(node) ) {
            // if there is, then we simply
            // unmark it
            node->is_terminal = 0;

            // tell the calling function
            // not to consider deleting any
            // other nodes up the tree anymore
            return 0;
        }
        else {
            // if no child nodes, then, we
            // can safely delete this node

            // we can simply deallocate this
            destroy_node(node);

            // tell the calling function
            // to start considering deleting
            // nodes up the tree, unless
            // one of the stopping conditions
            // is met: (1) a marker is found;
            // or (2) node has other children
            return 1;
        }

        return 0;
    }

    // helper functions to get the index
    // and the location of the path from
    // the array
    char alpha = str[pos];
    int idx = get_char_index(alpha);

    // check if the recursive call ended
    // up with losing one of its child nodes
    int has_lost_child = remove_string_recursive(node->children[idx], str, len, pos+1);

    if(has_lost_child) {
        // if a child node was deleted
        // then forget this reference
        // from the perspective of the parent
        node->children[idx] = NULL;

        // check first if this is the
        // root node now, because
        // we do not want to delete the
        // root node; if it is, then
        // we can safely stop the process
        if(pos == 0)
            return 0;

        // consider this for deletion, but
        // check first if one of the
        // stopping conditions is met:
        // (1) a marker is found;
        // or (2) node has other children
        if( node->is_terminal || has_children(node) ) {
            // other words need this node
            // so we can safely stop
            return 0;
        }
        else {
            // otherwise, we also remove
            // this node
            //destroy_node(node); // involves a loop that we can skip
            free(node);

            // inform the calling function
            // that we removed one of
            // its child nodes
            return 1;
        }
    }

    return 0;
}


int search(Trie *trie, char *str) {
    // create a pointer to the root
    TrieNode *ptr = trie->root;

    // traverse through each character
    // of the string
    int len = strlen(str);

    for(int i = 0; i < len; i++) {
        int idx = get_char_index(str[i]);

        // check if there is no existing
        // node for this letter
        if(ptr->children[idx] == NULL) {
            // this means that there is
            // no sense to continue further
            // since this current letter
            // doesn't exist in the trie
            // so return a 0 or false
            return 0;
        }

        // traverse to the next node
        ptr = ptr->children[idx];
    }

    // once we reached the last letter
    // ptr is pointing at the last node
    // therefore, do a final check to
    // see if this is a terminal node
    return ptr->is_terminal;
}


int has_children(TrieNode *node) {
    // in case this was called with no node
    if(node == NULL)
        return 0;

    // check if all of its children are NULL
    for(int i = 0; i < LETTER_COUNT; i++) {
        if(node->children[i] != NULL)
            return 1;
    }

    return 0;
}
