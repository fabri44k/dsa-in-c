/**
 * Stack OF INTEGERS using a singly linked list
 * https://www.wikiwand.com/en/articles/Stack_(abstract_data_type)
 * LIFO
 */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Initialize the Stack
 */
void create(Stack *s) {

    if (s == NULL) {
        fprintf(stderr, "Stack is NULL.\n");
        return;
    }

    s->head = NULL;
    s->count = 0;
}

/**
 * Push operand
 */
void push(Stack *s, int data) {

    Elem *e = malloc(sizeof(Elem));
    if (e == NULL) {
        fprintf(stderr, "Error when allocating memory\n");
        return;
    }

    e->data = data;
    e->next = s->head;

    s->head = e;
    s->count++;
    return;
}

/*
 * Pop Operand
 */
int pop(Stack *s) {

    if (s == NULL || s->head == NULL) {
        fprintf(stderr,
                "Unable to execute a pop on an empty stack. Returning -1\n");
        return -1;
    }

    int result = s->head->data;

    Elem *next = s->head->next;

    free(s->head);
    s->head = next;

    s->count--;

    return result;
}

/*
 * Returns 1 if the stack has no element, 0 otherwise
 * */
int is_empty(const Stack *s) {

    if (s == NULL)
        return 1;

    return (s->head == NULL);
}

/*
 * Returns the numeber of elements in the stack
 */
int get_length(const Stack *s) {

    if (s == NULL || s->head == NULL)
        return 0;

    return (s->count);
}

/*
 * Prints the stack
 */
void print(const Stack *s) {

    if (s == NULL || is_empty(s)) {
        fprintf(stderr, "\nEmpty Stack, unable to print\n");
        return;
    }

    Elem *current = s->head;

    while (current != NULL) {

        printf("-> [ %d ] ", current->data);
        current = current->next;
    }
    printf("\n");
}

/*
 * Peek operand
 * Get the last element, without removing
 */
int peek(const Stack *s) {
    if (s == NULL || s->head == NULL) {
        fprintf(stderr,
                "Unable to execute a peek on an empty stack. Returning -1\n");
        return -1;
    }

    return s->head->data;
}
