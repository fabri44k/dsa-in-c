#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Initialize the bst
 */
void create(Bst *bst) { bst->root = NULL; }

/*
 * Returns 1 if the bst has no nodes, 0 otherwise
 */
int is_empty(const Bst *bst) {

    if (bst == NULL) {
        fprintf(stderr, "Bst has not been initialized\n");
        return 1;
    }

    return (bst->root == NULL);
}

/*
 * Initialize and empty node with the provided data
 */
Node *create_new_node(int data) {

    Node *new = malloc(sizeof(Node));
    if (new == NULL) {
        fprintf(stderr, "Error when allocating memory\n");
        return NULL;
    }

    new->data = data;
    new->left = NULL;
    new->right = NULL;

    return new;
}

Node *search_helper(Node *start, int data) {

    if (start == NULL)
        return NULL;

    if (start->data == data)
        return start;

    if (start->data < data)
        return search_helper(start->right, data);
    else
        return search_helper(start->left, data);

    return NULL;
}

/*
 * Search the node with the provided data into the bst
 */
Node *search(const Bst *bst, int data) {

    if (bst == NULL) {
        fprintf(stderr, "Bst has not been initialized\n");
        return NULL;
    }

    if (is_empty(bst)) {
        return NULL;
    }

    Node *result = search_helper(bst->root, data);

    return result;
}

Node *insert_helper(Node *node, int data) {

    if (node == NULL)
        return create_new_node(data);

    if (node->data < data)
        node->right = insert_helper(node->right, data);
    else
        node->left = insert_helper(node->left, data);

    return node;
}

/*
 * Insert into the bst the node with the provided data
 */
void insert(Bst *bst, int data) {

    if (bst == NULL) {
        fprintf(stderr, "Bst has not been initialized\n");
        return;
    }

    bst->root = insert_helper(bst->root, data);

    return;
}

/*
 * Returns 1 if the provided node has a left children 0 otherwise
 */
int has_left_children(const Node *node) { return (node->left != NULL); }

/*
 * Returns 1 if the provided node has a right children 0 otherwise
 */
int has_right_children(const Node *node) { return (node->right != NULL); }

void print_subtree(const Node *node) {

    printf(" [ %d , ", node->data);

    if (has_left_children(node))
        print_subtree(node->left);
    else
        printf(" ");

    printf(",");

    if (has_right_children(node))
        print_subtree(node->right);
    else
        printf(" ");

    printf(" ] ");
}

/*
 * Prints the tree
 */
void print(const Bst *bst) {
    printf("\n");

    if (bst == NULL) {
        fprintf(stderr, "bst has not been initialized\n");
        return;
    }

    if (is_empty(bst)) {
        printf("Empty bst [] \n");
        return;
    }

    print_subtree(bst->root);

    printf("\n");
}

Node *father_helper(Node *current, Node *previous, int data) {

    if (current == NULL)
        return NULL;

    if (current->data == data)
        return previous;

    if (current->data < data)
        return father_helper(current->right, current, data);
    else
        return father_helper(current->left, current, data);
}

Node *get_father(Bst *bst, Node *node) {

    if (node == NULL || bst == NULL || bst->root == NULL)
        return NULL;

    if (bst->root == node || bst->root->data == node->data)
        return NULL;

    Node *father = father_helper(bst->root, NULL, node->data);

    return father;
}

Node *minimum_helper(Node *node) {

    if (node->left == NULL)
        return node;

    if (has_left_children(node)) {
        return minimum_helper(node->left);
    }

    return NULL;
}

/*
 * Find the minimum node in the bst
 */
Node *minimum(const Bst *bst) {
    if (bst == NULL) {
        fprintf(stderr, "bst has not been initialized\n");
        return NULL;
    }

    if (is_empty(bst)) {
        return NULL;
    }

    return minimum_helper(bst->root);
}

Node *maximum_helper(Node *node) {

    if (node->right == NULL)
        return node;

    if (has_right_children(node)) {
        return maximum_helper(node->right);
    }

    return NULL;
}

/*
 * Find the maximum node in the bst
 */
Node *maximum(const Bst *bst) {
    if (bst == NULL) {
        fprintf(stderr, "bst has not been initialized\n");
        return NULL;
    }

    if (is_empty(bst)) {
        return NULL;
    }

    return maximum_helper(bst->root);
}
/*
 * Inorder Successor: The node with the smallest key greater than the given key
 * (minimum in the right subtree)
 */
Node *successor(Node *node) {
    if (node == NULL || node->right == NULL)
        return NULL;

    Node *successor = minimum_helper(node->right);
    return successor;
    // iterative solution (redundant code)
    // Node *start = node->right;

    // while (start->left != NULL) {

    //     start = start->left;
    // }
    // return start;
}

/*
 * Inorder Predecessor: The node with the largest key smaller than the given
 * key (maximum in the left subtree) used for deletion
 */
Node *predecessor(Node *node) {

    if (node == NULL || node->left == NULL)
        return NULL;

    Node *predecessor = maximum_helper(node->left);

    return predecessor;
    // iterative solution (redundant code)
    // Node *start = node->left;

    // while (start->right != NULL) {

    //     start = start->right;
    // }
    // return start;
}

/*
 * Delete the provided node with data from the bst
 *
 */
void delete_node(Bst *bst, int data) {

    if (bst == NULL) {
        fprintf(stderr, "bst has not been initialized\n");
        return;
    }

    if (is_empty(bst)) {
        return;
    }

    // check if the node exist before starting the deletion
    Node *node = search(bst, data);

    if (node == NULL) {
        printf("Node has not been found, unable to delete\n");
        return;
    }

    // case 1 leaf node
    if (node->left == NULL && node->right == NULL) {
        Node *father = get_father(bst, node);

        // deleting the root node
        if (father == NULL) {
            free(node);
            bst->root = NULL;
            return;
        } else {
            if (father->left == node) {
                father->left = NULL;
            } else {
                father->right = NULL;
            }
            free(node);
        }
        return;
    } // Case 2: Deleting a Node with One Child
    else if ((node->left != NULL && node->right == NULL) ||
             (node->left == NULL && node->right != NULL)) {

        Node *son = node->left;
        if (son == NULL) {
            son = node->right;
        }
        Node *father = get_father(bst, node);
        if (father == NULL) {
            bst->root = son;
            free(node);
            return;
        } else {
            if (father->left == node) {
                father->left = son;
            } else {
                father->right = son;
            }
            free(node);
        }
        return;
    } // Case 3: Deleting a Node with Two Children
    else {
        // finding predecessor of the node
        Node *pred = predecessor(node);

        if (pred == NULL) {
            fprintf(stderr, "Error finding predecessor when deleting node %d",
                    node->data);
            return;
        }

        int temp = pred->data;
        delete_node(bst, pred->data);
        node->data = temp;
        return;
    }

    return;
}

void destroy_helper(Node *node) {
    if (node == NULL) {
        return;
    }

    destroy_helper(node->left);

    destroy_helper(node->right);

    free(node);
}

/**
 * Free all the memory of the bst
 */
void destroy_tree(Bst *bst) {
    if (bst == NULL) {
        fprintf(stderr, "bst has not been initialized\n");
        return;
    }

    destroy_helper(bst->root);
    bst->root = NULL;
}
