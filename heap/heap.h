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
size_t get_heap_size(const heap *);
int is_empty(const heap *);
int peek_max(const heap *);

void insert(heap *, int);
int extract_max(heap *);
void delete_max(heap *);
void print_heap(const heap *);

#endif // HEAP_H
