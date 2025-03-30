#include <stdio.h>
#include <stdlib.h>
#define LETTER_COUNT 26

// Sample C Implementation of a trie.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-29.


typedef struct TrieNode_s {
    struct TrieNode_s *children[LETTER_COUNT];
    int is_end;
} TrieNode;

typedef struct Trie_s {
    TrieNode *root;
} Trie;


// function prototypes
Trie * create_trie();
TrieNode * create_node();
void destroy_trie(Trie *);
void destroy_node(TrieNode *);
void insert(Trie *, char *);
void remove_string(Trie *, char *);
int search(Trie *, char *);


int main(void) {
    // create a trie
    Trie *trie = create_trie();



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
    node->is_end = 0;

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
