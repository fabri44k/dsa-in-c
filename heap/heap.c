#include "heap.h"
#include <stdio.h>

void create_heap(heap *h) {

    h->size = 0;
    h->capacity = DEFAULT_SIZE;

    h->array = malloc(DEFAULT_SIZE * sizeof(int));

    if (h->array == NULL) {
        fprintf(stderr, "Error when allocating memory");
        return;
    }

    return;
}

/**
 * Return 1 if empty 0 if not
 */
int is_empty(const heap *h) {

    if (h == NULL) {
        fprintf(stderr, "Provided heap is not inizialized");
    }

    return (h->size == 0);
}

size_t get_heap_size(const heap *h) {
    if (h == NULL) {
        fprintf(stderr, "Provided heap is not inizialized");
    }
    return (h->size);
}

int peek_max(const heap *h) {
    if (h == NULL) {
        fprintf(stderr, "Provided heap is not inizialized");
    }
    if (is_empty(h)) {
        fprintf(stderr, "Provided heap is empty");
    }
    return h->array[0];
}

size_t get_parent_index(size_t index) {
    if (index == 0) {
        return 0;
    }
    return ((index - 1) / 2);
}

size_t get_left_child_index(size_t index) { return (2 * index + 1); }

size_t get_right_child_index(size_t index) { return (2 * index + 2); }

void resize_heap(heap *h) {
    size_t new_cap = h->capacity * 2;

    int *new = realloc(h->array, new_cap * sizeof(int));

    if (new == NULL) {
        fprintf(stdout, "Error when reallocating");
        return;
    }

    h->array = new;
    h->capacity = new_cap;
    return;
}

void print_heap(const heap *h) {

    if (is_empty(h)) {
        printf("Empty heap [ ]\n");
        return;
    }
    printf("[ ");
    for (size_t i = 0; i < h->size; ++i) {
        printf(" %d ,", h->array[i]);
    }

    printf(" ]\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

/**
 * Insert a new value into the heap
 */
void insert(heap *h, int data) {

    if (h->capacity == h->size) {
        resize_heap(h);
    }
    int current = h->size;

    h->array[current] = data;
    h->size++;

    int parent_index = get_parent_index(current);

    while (current > 0 && (h->array[current] > h->array[parent_index])) {
        swap(&h->array[current], &h->array[parent_index]);
        current = parent_index;
        parent_index = get_parent_index(current);
    }
    return;
}

/**
 * Extract max value from the heap.
 */
int extract_max(heap *h) {

    if (is_empty(h)) {
        fprintf(stderr, "Provided heap is empty");
        return 0;
    }

    // take the root node
    int value = h->array[0];

    // case only one element
    if (h->size == 1) {
        h->size--;
        return value;
    }

    // replacing the old root with the last element
    h->array[0] = h->array[h->size - 1];
    // deleting last node
    h->size--;

    // heap property

    size_t curr = 0;
    size_t left = 1;
    size_t right = 2;
    size_t largest = left;

    while (left < h->size) {

        // find the largest node
        largest = left;

        if (right < h->size && h->array[left] < h->array[right]) {
            largest = right;
        }

        if (h->array[curr] < h->array[largest]) {

            swap(&h->array[curr], &h->array[largest]);
            curr = largest;
        } else {
            break;
        }

        left = 2 * curr + 1;
        right = 2 * curr + 2;
    }

    return value;
}
