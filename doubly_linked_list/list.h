#ifndef LISTA_H
#define LISTA_H

struct Node {
    struct Node *prev;
    int value;
    struct Node *next;
};
typedef struct Node Node;

struct List {
    Node *head;
    Node *tail;
    int length;
};
typedef struct List List;

void create(List *);
int get_length(const List *);
int is_empty(const List *);
int read(const List *, const int);
Node *first_node(const List *);
Node *last_node(const List *);
void insert(List *, int, int);
void append(List *, int);
void write(List *, int, int);
void deleteAt(List *, int);
void print(const List *);
int linear_search(const List *, int);
void reverse(List *);

#endif
