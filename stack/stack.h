/**
 * Stack OF INTEGERS using a singly linked list
 * https://www.wikiwand.com/en/articles/Stack_(abstract_data_type)
 * LIFO
 */
#ifndef STACK_H
#define STACK_H

struct elem {
    struct elem *next;
    int data;
};
typedef struct elem Elem;

struct stack {
    Elem *head;
    int count;
};
typedef struct stack Stack;

void create(Stack *);

void push(Stack *, int);

int pop(Stack *);

int get_length(const Stack *);

int is_empty(const Stack *);

void print(const Stack *);

int peek(const Stack *);

#endif // !STACK_H
