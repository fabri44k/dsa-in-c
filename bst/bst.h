/**
 * Binary search tree OF INTEGERS
 *
 */
#ifndef BST_H
#define BST_H

struct node {
    struct node *left;
    int data;
    struct node *right;
};
typedef struct node Node;

struct bst {
    Node *root;
};
typedef struct bst Bst;

void create(Bst *);
int is_empty(const Bst *);
void insert(Bst *, int);
Node *search(const Bst *, int);
Node *minimum(const Bst *);
Node *maximum(const Bst *);
void print(const Bst *);

void delete_node(Bst *, int);
Node *predecessor(Node *);
Node *successor(Node *);
void destroy_tree(Bst *);

#endif // !BST_H
