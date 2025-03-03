#include <stdio.h>
#include <stdlib.h>

// Sample C Implementation of a binary search tree.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-02.

typedef struct BSTNode_s {
    int data;
    struct BSTNode_s *left;
    struct BSTNode_s *right;
} BSTNode;

typedef struct BSTree_s {
    BSTNode *root;
} BSTree;


// maintenance
BSTree * create_tree();
void destroy_tree(BSTree *);
BSTNode * create_node(int);
void destroy_node(BSTNode *);

// function prototypes
void insert(BSTree *, int);
BSTNode * search(BSTree *, int);
BSTNode * remove_node(BSTree *, int);
void inorder(BSTNode *);
void preorder(BSTNode *);
void postorder(BSTNode *);
int is_empty(BSTree *);


int main(void) {
    BSTree *tree = create_tree();

    // insert the following values
    insert(tree, 50);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 10);
    insert(tree, 5);
    insert(tree, 90);

    // traversal
    inorder(tree->root);

    return 0;
}


BSTree * create_tree() {
    BSTree *tree = malloc(sizeof(BSTree));

    tree->root = NULL;

    return tree;
}


void destroy_tree(BSTree *tree) {
    // currently assume that there are no nodes
    // anymore
    if( is_empty(tree) ) {
        free(tree);
    }
}


BSTNode * create_node(int val) {
    // create a new node
    BSTNode *node = malloc(sizeof(BSTNode));

    // set the attributes
    node->data = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}


void destroy_node(BSTNode *node) {
    free(node);
}


void insert(BSTree *tree, int val) {
    // if it is empty, set the root
    if( is_empty(tree) ) {
        tree->root = create_node(val);
        return;
    }

    // find the correct location
    BSTNode *ptr = tree->root;

    while(1) {
        // go to the left?
        if(val < ptr->data) {
            // check if left is not null
            if(ptr->left == NULL) {
                // create the node here
                ptr->left = create_node(val);
                return;
            }
            ptr = ptr->left;
        }
        else {
            // check if right is not null
            if(ptr->right == NULL) {
                // create the node here
                ptr->right = create_node(val);
                return;
            }
            ptr = ptr->right;
        }
    }
}


int is_empty(BSTree *tree) {
    return tree->root == NULL;
}


void inorder(BSTNode *node) {
    // recursive visit
    // LVR
    // left
    if(node->left != NULL) {
        inorder(node->left);
    }

    // visit
    printf("%d\n", node->data);

    // right
    if(node->right != NULL) {
        inorder(node->right);
    }
}
