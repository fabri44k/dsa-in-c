/**
 * MAX Heap of Integers
 */

#include <stdlib.h>

#ifndef HEAP_H
#define HEAP_H

#define DEFAULT_SIZE 10

struct heap {
    int *array;
    size_t capacity;
    size_t size;
};
typedef struct heap heap;

void create_heap(heap *);
void add_array_to_heap(heap *, int *, size_t);
size_t get_heap_size(const heap *);
int is_empty(const heap *);
int peek_max(const heap *);
void insert(heap *, int);
void print_heap(const heap *);

int extract_max(heap *);

#endif // HEAP_H
