/**
 * Hash table implementation using
 *
 * dynamic array
 * dj2b hash
 * linear probing
 * Reallocation of the enire table based on the load factor
 * Lazy deletion
 *
 * TYPES:
 * [STRING] -> INTEGER ([KEY] -> DATA)
 *
 */
#include <stddef.h>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct pair {
    int data;
    char *key;
};
typedef struct pair Pair;

struct hash_table {
    size_t size;
    Pair **data_array;
    size_t count;
};
typedef struct hash_table HashTable;

void create(HashTable *, size_t);
int is_empty(const HashTable *);
int has_item(const HashTable *, int);
void insert(HashTable *, char *, int);
int get_item(const HashTable *, char *);
void delete_item(HashTable *, char *);
void print(const HashTable *);
void destroy(HashTable *);

#endif // HASH_TABLE_H
