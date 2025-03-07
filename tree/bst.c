#include <stdio.h>
#include <stdlib.h>

// Sample C Implementation of a binary search tree.
// This combines all the codes covered during the lecture.
// Please report any bug you may find.
// This code was last updated on 2025-03-06.

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
BSTNode * find_sucessor_with_parent(BSTNode *, BSTNode **);
BSTNode * find_predecessor(BSTNode *);
BSTNode * node_removal_helper(BSTree *, BSTNode *, BSTNode *);
void postorder_destroy_nodes(BSTNode *);


int main(void) {
    BSTree *tree = create_tree();

    // insert the following values
    insert(tree, 50);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 10);
    insert(tree, 5);
    insert(tree, 90);
    insert(tree, 100);

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


    // delete node
    tmp = remove_node(tree, 90);
    if(tmp) {
        printf("Deleted!\n");

        // deallocate this node
        destroy_node(tmp);
    }

    // inorder traversal
    printf("In-Order Traversal:\n");
    inorder(tree->root);


    // destroy the tree
    destroy_tree(tree);

    return 0;
}


BSTree * create_tree() {
    // dynamically allocate the tree
    // and set the root to NULL to indicate
    // and empty tree
    BSTree *tree = malloc(sizeof(BSTree));

    tree->root = NULL;

    return tree;
}


void destroy_tree(BSTree *tree) {
    // helper function to destroy the entire
    // tree by deallocating all the nodes
    // then eventually the tree itself

    // destroy all the nodes first
    postorder_destroy_nodes(tree->root);

    // destroy the tree
    free(tree);
}


BSTNode * create_node(int val) {
    // helper function to simply create a new
    // node and set the data attribute
    // it then initializes the left and right child
    // to be both NULL
    BSTNode *node = malloc(sizeof(BSTNode));

    // set the attributes
    node->data = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}


void destroy_node(BSTNode *node) {
    // destroy the node
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


BSTNode * remove_node(BSTree *tree, int query) {
    // assumption is that the data of all
    // the nodes of the tree is distinct

    // check first if the tree is empty
    if( is_empty(tree) ) {
        return NULL;
    }

    // there are three scenarios for this
    // operation, therefore we have to
    // handle each scenario differently

    // find the actual node first
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
    // BST property; keep going down until
    // the correct node is found OR if
    // we have reached the end
    while(ptr != NULL) {
        // keep on going down the tree
        // until we find query!

        // check if this is what we are
        // looking for, if it is, then
        // proceed with the deletion
        if(ptr->data == query) {
            // do the deletion here
            // to simplify the code, we are
            // going to do a function call
            // to a helper function that
            // performs the actual deletion
            return node_removal_helper(tree, ptr, parent);
        }

        // update the parent pointer
        // because ptr is about to change
        parent = ptr;

        // update ptr now by determining
        // whether to go to the left or
        // right based on the BST property
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

    return NULL;
}


void inorder(BSTNode *node) {
    // this is the base case
    if(node == NULL) {
        return;
    }

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
    // this is the base case
    if(node == NULL) {
        return;
    }

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
    // this is the base case
    if(node == NULL) {
        return;
    }

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

    // check first if there is a potential
    // successor
    if(node->right == NULL) {
        return NULL;
    }

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


BSTNode * find_sucessor_with_parent(BSTNode *node, BSTNode **parent) {
    // this is another helper function that accepts
    // an extra parameter which is a pointer to a pointer
    // to a node; the idea is to be able to return two
    // information when this function is called;
    // the first is to return the successor of node while
    // the second is to provide details about the parent
    // of this successor node; therefore, we use the
    // parent argument to be able to "modify" this
    // from within this function and to relay the
    // information to the calling function
    // (pass by reference)

    // idea is to find the small value
    // that is located on the right subtree of
    // the node; in short, go to the right once
    // then go all the way to the left until
    // reach the end

    // check first if there is a potential
    // successor
    if(node->right == NULL) {
        return NULL;
    }

    BSTNode *ptr = node->right;
    // we add a trailing pointer
    // that just keeps the old value
    // of ptr; initialized to NULL
    // to prevent logic error when
    // there is no successor at all
    BSTNode *trail = node;
    // parent will be the trailing pointer
    // for the trail (later will be a pointer
    // to the parent of the actual successor
    // note that this was passed as an address
    // therefore, we need to dereference it
    *parent = NULL;

    // go all the way to the left
    // stop only when the end is reached
    while(ptr != NULL) {
        // update the parent pointer
        *parent = trail;

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


BSTNode * node_removal_helper(BSTree *tree, BSTNode *ptr, BSTNode *parent) {
    // this is a helper function that does the
    // actual deletion and accounts for the 3
    // different scenarios; ptr is the node we want
    // to delete while parent is the parent of ptr

    // Scenario 1: what we want to delete do
    // not have any children; therefore, just
    // cut it off; we do this by telling the
    // parent that ptr won't be their child anymore
    // follow the BST property to determine which
    // child is going to be cut off
    if(ptr->left == NULL && ptr->right == NULL) {
        printf("Scenario 1\n");

        // check if ptr is the root because
        // it doesn't have a parent
        if(parent == NULL) {
            // then ptr is the only node
            // in the tree, therefore making
            // it an empty tree afterward
            tree->root = NULL;
        }
        else {
            // check if ptr is left child of
            // its parent or otherwise
            if(ptr->data < parent->data) {
                parent->left = NULL;
            }
            else {
                parent->right = NULL;
            }
        }

        // reference to the node we just deleted
        return ptr;
    }

    // Scenario 2: what we want to delete has
    // one child; therefore, we simply cut off
    // ptr and promote its only child to be the
    // new child of the parent of ptr
    if((ptr->left == NULL && ptr->right != NULL) || (ptr->left != NULL && ptr->right == NULL)) {
        printf("Scenario 2\n");
        // obtain a pointer to the only child of ptr
        BSTNode *child;
        if(ptr->left != NULL) {
            child = ptr->left;
        }
        else {
            child = ptr->right;
        }

        // check if this node has a parent
        // meaning if there is no parent, it is the
        // root; therefore, impacting how the child
        // will be promoted; it becomes the new root
        if(parent == NULL) {
            tree->root = child;
        }
        else {
            // promote the child by one level
            // this means, the child will have a new
            // parent; the parent will be the parent
            // of ptr (node we want to delete);
            // we still have to figure out first
            // if ptr is which child of its parent
            // whether left or right (BST property)
            if(ptr->data < parent->data) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }

        // reference to the node we just deleted
        return ptr;
    }

    // Scenario 3: what we want to delete has
    // two children; we perform a deletion by copying
    // the idea is to find the successor of ptr then
    // have the data value of the successor take the place
    // of ptr (we do not delete the ptr node per se);
    // rather, what we will be deleting will be the node
    // of ptr's successor; note that it will be possible
    // for the successor to have a right subtree BUT
    // not a left subtree; why? because if there was a left
    // subtree, then this is not the true successor of ptr!
    // what this implies is that it is possible for
    // for scenario 3 to end up with a scenario 1 or 2 as
    // what we will be deleting will be the successor node!
    if(ptr->left != NULL && ptr->right != NULL) {
        printf("Scenario 3\n");
        // find the successor of ptr using the other
        // version of the function capable of returning
        // the information about the parent of the node
        BSTNode *parent_of_successor;
        BSTNode *successor = find_sucessor_with_parent(ptr, &parent_of_successor);

        printf("\tSuccessor: %d and Parent: %d\n", successor->data, parent_of_successor->data);

        // simply copy the data value of the successor
        // and retain the actual ptr node
        ptr->data = successor->data;

        // we now perform a delete at the successor!
        return node_removal_helper(tree, successor, parent_of_successor);
    }

    return NULL;
}


void postorder_destroy_nodes(BSTNode *node) {
    // this is the base case
    if(node == NULL) {
        return;
    }

    // recursive visit which begins at
    // the root node
    // follows the order: LRV

    // left; if there is a left child
    if(node->left != NULL) {
        postorder_destroy_nodes(node->left);
    }

    // right; if there is a right child
    if(node->right != NULL) {
        postorder_destroy_nodes(node->right);
    }

    // visit the current node
    free(node);
}
