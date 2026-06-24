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

    int value = h->array[0];

    if (h->size == 1) {
        h->size--;
        return value;
    }

    h->array[0] = h->array[h->size - 1];
    h->size--;

    size_t current = 0;

    int right_ch_index = get_right_child_index(current);
    int *right_ch = &h->array[right_ch_index];

    int left_ch_index = get_left_child_index(current);
    int *left_ch = &h->array[left_ch_index];

    int larger_ch_index =
        (*right_ch >= *left_ch) ? right_ch_index : left_ch_index;

    while (current < h->size &&
           (h->array[current] < *right_ch || h->array[current] < *left_ch)) {
        swap(&h->array[current], &h->array[larger_ch_index]);
        current = larger_ch_index;

        right_ch_index = get_right_child_index(current);
        right_ch = &h->array[right_ch_index];

        left_ch_index = get_left_child_index(current);
        left_ch = &h->array[left_ch_index];

        larger_ch_index =
            (*right_ch >= *left_ch) ? right_ch_index : left_ch_index;
    }

    return value;
}
