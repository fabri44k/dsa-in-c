/**
 * Binary search tree OF INTEGERS using:
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

void erase(Bst *, int);
Node *predecessor(Bst *, Node *);
Node *successor(Bst *, Node *);

#endif // !BST_H
