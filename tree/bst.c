#include <stdio.h>
#include <stdlib.h>

// Sample C Implementation of a binary search tree.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-03.

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

// helper functions
int is_empty(BSTree *);
BSTNode * find_sucessor(BSTNode *);
BSTNode * find_predecessor(BSTNode *);


int main(void) {
    BSTree *tree = create_tree();

    // insert the following values
    insert(tree, 50);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 10);
    insert(tree, 5);
    insert(tree, 90);

    // inorder traversal
    printf("In-Order Traversal:\n");
    inorder(tree->root);

    // preorder traversal
    printf("Pre-Order Traversal:\n");
    preorder(tree->root);

    // postorder traversal
    printf("Post-Order Traversal:\n");
    postorder(tree->root);

    BSTNode *tmp;

    // search for a value
    tmp = search(tree, 90);
    if(tmp) {
        printf("Found!\n");
    }
    else {
        printf("Not Found!\n");
    }

    tmp = search(tree, 5);
    if(tmp) {
        printf("Found!\n");
    }
    else {
        printf("Not Found!\n");
    }

    tmp = search(tree, 75);
    if(tmp) {
        printf("Found!\n");
    }
    else {
        printf("Not Found!\n");
    }


    // determine the successor of nodes
    printf("Successor:\n");
    tmp = find_sucessor(tree->root);
    if(tmp) {
        printf("Next: %d\n", tmp->data);
    }


    // destroy the tree
    destroy_tree(tree);

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
    // we need to add another pointer
    // which holds to old value of ptr
    // as ptr moves to the next node;
    // essentially, think of it as the
    // parent of ptr
    BSTNode *parent = NULL;

    // currently the tree is not empty
    // so we just have to find the correct
    // location of the value based on the
    // BST property; we know that we have
    // found the correct location of
    // the new value if that is an empty
    // spot; otherwise, keep on looking for
    // an empty spot where we can create
    // the new node
    while(ptr != NULL) {
        // keep on going down the tree
        // until we find an empty spot!

        // update the parent pointer
        // because ptr is about to change
        parent = ptr;

        // update ptr now by determining
        // whether to go to the left or
        // right based on the BST property
        // if what we are about to insert is
        // less than the current node, we
        // should go left; otherwise, go right
        if(val < ptr->data) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
    }

    // at this point, we have already found
    // an empty spot because ptr is already
    // NULL; what's left to do is to look
    // at where parent is pointing at because
    // it will be the parent of the new
    // node that we will be creating
    // we just need to know if the node we are
    // going to create will become either
    // the left child or the right child
    // of the parent node; again, BST property
    if(val < parent->data) {
        parent->left = create_node(val);
    }
    else {
        parent->right = create_node(val);
    }
}


BSTNode * search(BSTree *tree, int query) {
    // assumption is that the data of all
    // the nodes of the tree is distinct

    // check first if the tree is empty
    if( is_empty(tree) ) {
        return NULL;
    }

    // find the node that has a data
    // value of what we are looking for
    // we need a pointer variable that
    // is moving down the tree; the idea
    // of a moving pointer is similar to
    // the ptr variable we used with the
    // linked list; similarly, we start
    // pointing at the entry point of the
    // tree which is the root node
    BSTNode *ptr = tree->root;

    // keep on moving the pointer
    // until reach the end of a path;
    // in short, when ptr points to NULL
    while(ptr != NULL) {
        // check if the current node is what
        // we are looking for
        if(ptr->data == query) {
            return ptr;
        }

        // determine whether to go to
        // the left or to the right
        // the BST property determines
        // our next move (node):
        // if what we are looking for is
        // less than the current node, we
        // should go left; otherwise, go right
        if(query < ptr->data) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
    }

    return ptr;
}


void inorder(BSTNode *node) {
    // recursive visit which begins at
    // the root node
    // follows the order: LVR

    // left; if there is a left child
    if(node->left != NULL) {
        inorder(node->left);
    }

    // visit the current node
    printf("%d\n", node->data);

    // right; if there is a right child
    if(node->right != NULL) {
        inorder(node->right);
    }
}


void preorder(BSTNode *node) {
    // recursive visit which begins at
    // the root node
    // follows the order: VLR

    // visit the current node
    printf("%d\n", node->data);

    // left; if there is a left child
    if(node->left != NULL) {
        preorder(node->left);
    }

    // right; if there is a right child
    if(node->right != NULL) {
        preorder(node->right);
    }
}


void postorder(BSTNode *node) {
    // recursive visit which begins at
    // the root node
    // follows the order: LRV

    // left; if there is a left child
    if(node->left != NULL) {
        postorder(node->left);
    }

    // right; if there is a right child
    if(node->right != NULL) {
        postorder(node->right);
    }

    // visit the current node
    printf("%d\n", node->data);
}


int is_empty(BSTree *tree) {
    // check if the tree is empty by
    // simply inspecting if the root is
    // NULL or not
    return tree->root == NULL;
}


BSTNode * find_sucessor(BSTNode *node) {
    // idea is to find the small value
    // that is located on the right subtree of
    // the node; in short, go to the right once
    // then go all the way to the left until
    // reach the end
    BSTNode *ptr = node->right;
    // we add a trailing pointer
    // that just keeps the old value
    // of ptr; initialized to NULL
    // to prevent logic error when
    // there is no successor at all
    BSTNode *trail = NULL;

    // go all the way to the left
    // stop only when the end is reached
    while(ptr != NULL) {
        // update the trailing pointer
        trail = ptr;

        // update ptr to point to
        // the left node
        ptr = ptr->left;
    }

    // once we reached the end,
    // the last node will be pointed
    // at by trail, therefore return this
    return trail;
}
