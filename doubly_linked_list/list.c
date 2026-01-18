/** Symmetric list OF INTEGERS
 * HEAD -> [prevNode][value][nextNode] -> ...
 * https://en.wikipedia.org/wiki/Doubly_linked_list
 */
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Create an empty list
 * */
void create(List *l) {

    if (l == NULL)
        return;

    l->head = NULL;
    l->tail = NULL;
    l->length = 0;
}

/**
 * Get the list dimension
 * returns -1 if the list has not been created yet
 * */
int get_length(const List *l) {

    if (l == NULL)
        return -1;

    return l->length;
}

/**
 * Checks if the list is empty
 * */
int is_empty(const List *l) {

    if (l == NULL)
        return 1;

    return (l->head == NULL);
}

/**
 * Get a pointer to the first node of the list
 * */
Node *first_node(const List *l) {

    if (l == NULL)
        return NULL;

    return (l->head);
}

/**
 * Get a pointer to the last node of the list
 * */
Node *last_node(const List *l) {

    if (l == NULL)
        return NULL;

    return (l->tail);
}

/**
 * Read the element of the list at pos position
 * */
int read(const List *l, int pos) {

    if (l == NULL) {
        printf("Unable to read on an uninitialized list. Returning -1");
        return -1;
    }

    if (pos >= l->length || pos < 0 || is_empty(l)) {
        printf("Empty list or invalid position. Returning -1\n");
        return -1;
    }

    Node *current = first_node(l);
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }

    return current->value;
}

/**
 * Add a value when the list is empty
 **/
void insert_in_empty_list(List *l, int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }

    new_node->prev = NULL;
    new_node->value = value;
    new_node->next = NULL;

    l->head = new_node;
    l->tail = new_node;
    l->length = 1;
}

/**
 * Add value in the last position, append operation
 * */
void append(List *l, int value) {

    if (l == NULL) {
        fprintf(stderr, "Error the provided list has not been initialized\n");
        return;
    }

    if (is_empty(l)) {

        insert_in_empty_list(l, value);

        return;
    }

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }

    new_node->value = value;
    new_node->next = NULL;

    Node *current = last_node(l);

    current->next = new_node;
    new_node->prev = current;
    l->tail = new_node;
    l->length++;
}
/**
 * Add value in the first position
 * */
void insert_at_first_position(List *l, int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }

    new_node->value = value;
    new_node->next = l->head;
    new_node->prev = NULL;

    if (l->head != NULL) {
        l->head->prev = new_node;
    }

    l->head = new_node;
    if (l->length == 0)
        l->tail = new_node;
    l->length++;
}

/**
 * Add value in pos position
 * */
void insert(List *l, int pos, int value) {

    if (l == NULL)
        return;

    if (pos < 0 || pos > l->length) {
        printf("Negative or over position\n");
        return;
    }

    if (is_empty(l)) { // inserimento su lista vuota, ignori il valore di pos

        insert_in_empty_list(l, value);

        return;

    } else if (pos == 0) { // inserimento in testa

        insert_at_first_position(l, value);

        return;

    } else if (pos == l->length) { // inserimento in coda

        append(l, value);

        return;

    } else { // inserimento in mezzo

        Node *current = first_node(l);
        int i = 0;

        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL) {
            printf("Errore: allocazione memoria fallita\n");
            return;
        }

        while (current != NULL) {

            if (i == pos - 1) {

                Node *temp = current->next;

                new_node->prev = current;

                new_node->value = value;

                new_node->next = temp;

                current->next = new_node;

                temp->prev = new_node;

                l->length++;
                break;
            }

            current = current->next;
            i++;
        }
    }
}

/**
 * Overwrite value in pos position
 * */
void write(List *l, int pos, int value) {
    if (l == NULL)
        return;

    if (pos >= l->length || pos < 0) {
        printf("Invalid position. Returning.\n");
        return;
    }

    Node *current = first_node(l);
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }

    current->value = value;
    return;
}

/**
 * Delete the node at pos position
 * */
void deleteAt(List *l, int pos) {
    if (l == NULL)
        return;

    if (pos >= l->length || pos < 0) {
        printf("Invalid position. Returning.\n");
        return;
    }

    Node *to_delete = first_node(l);
    for (int i = 0; i < pos; i++) {
        to_delete = to_delete->next;
    }

    Node *prev_node = to_delete->prev;
    Node *next_node = to_delete->next;

    if (prev_node != NULL) {
        prev_node->next = next_node;
    } else {
        l->head = next_node;
    }

    if (next_node != NULL) {
        next_node->prev = prev_node;
    }

    free(to_delete);

    l->length--;
}

/**
 * Print the list
 */
void print(const List *l) {
    if (l == NULL || is_empty(l)) {
        printf("\nLista vuota\n");
        return;
    }
    Node *current = l->head;
    while (current != NULL) {
        printf("-> [ %d ] ", current->value);
        current = current->next;
    }
    printf("\n");
}

/**
 * Search value into the list.
 * Linear search
 * Return the first position where the value is present, -1 if not.
 */
int linear_search(const List *l, int value) {

    if (l == NULL || l->length == 0) {
        return -1;
    }

    int index = 0;
    Node *current = first_node(l);
    while (current != NULL && index < l->length) {
        if (current->value == value)
            return index;
        index++;
        current = current->next;
    }

    return -1;
}

/**
 * Reverse the order of its elements.
 * O(n) time compelxity
 */
void reverse(List *l) {

    if (l == NULL || l->length == 0) {
        printf("Unable to reverse an empty list");
        return;
    }

    Node *current = l->head;
    Node *temp = NULL;

    while (current != NULL) {

        temp = current->prev;

        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    temp = l->head;

    l->head = l->tail;

    l->tail = temp;

    return;
}

/**
 * Reverse the order of its elements.
 * O(n^2) time complexity
 */
void reverse_quadratic(List *l) {

    if (l == NULL || l->length == 0) {

        printf("Unable to reverse an empty list");

        return;
    }

    int start = 0;

    int end = l->length - 1;

    while (start < end) {

        int temp_value = read(l, end);

        write(l, end, read(l, start));

        write(l, start, temp_value);

        start++;

        end--;
    }

    return;
}
