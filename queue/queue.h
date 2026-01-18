/**
 * Queue OF INTEGERS implementation using a singly linked list.
 * https://www.wikiwand.com/en/articles/Queue_(abstract_data_type)
 * FIFO
 */
#ifndef QUEUE_H
#define QUEUE_H

struct elem {
    struct elem *next;
    int data;
};
typedef struct elem Elem;

struct queue {
    Elem *head;
    Elem *tail;
    int count;
};
typedef struct queue Queue;

void create(Queue *);

void enqueue(Queue *, int);

int dequeue(Queue *);

int get_length(const Queue *);

int is_empty(const Queue *);

void print(const Queue *);

int front(const Queue *);

#endif // QUEUE_H
