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
