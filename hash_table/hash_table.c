#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* when the load factor is greater than this value the hashtable is reallocated
 */
#define REALLOCATION_THRESHOLD 0.7

/* Tombstone pair, reprsent a removed value */
static Pair DELETED_ITEM = {0, NULL};

/**
 * Utility function
 * Duplicates a string by allocating memory and copying the content.
 * Returns a pointer to the new string or NULL if allocation fails.
 * This is similar to the strdup function
 * if you dont use this function, if you pass a pointer to the insert function,
 * then you modify the value stored through that same pointer, the hash table
 * will have an altered key value.
 */
char *string_duplicate(const char *src) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = strlen(src) + 1;

    char *dst = malloc(len);
    if (dst == NULL) {
        fprintf(stderr, "Error when allocating memory for string\n");
        return NULL;
    }

    if (dst != NULL) {
        memcpy(dst, src, len);
    }

    return dst;
}

/*
 * Initialize the hast table with max dimension starting_size
 */
void create(HashTable *ht, size_t starting_size) {

    if (ht == NULL) {
        fprintf(stderr, "Error when creating hash table\n");
        return;
    }

    ht->data_array = calloc(starting_size, sizeof(Pair *));

    if (ht->data_array == NULL) {
        fprintf(stderr, "Error when allocating memory");
        return;
    }
    ht->size = starting_size;
    ht->count = 0;
}

/*
 * Returns 1 if the hash table has no elements, 0 otherwise
 */
int is_empty(const HashTable *ht) {

    if (ht == NULL)
        return 1;

    return (ht->count == 0);
}

/**
 * djb2 hasing
 */
unsigned long hash(const unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

/*
 * Reallocate space doubling the old size
 * Returns 0 if success, 1 if not
 */
int reallocate_table(HashTable *ht) {

    // new size is obtained doubling the size
    size_t old_size = ht->size;
    size_t new_size = old_size * 2;

    Pair **new_array = calloc(new_size, sizeof(Pair *));
    if (new_array == NULL) {
        fprintf(stderr, "Error when reallocating memory\n");
        return 1;
    }

    // rehashing pairs
    for (size_t i = 0; i < old_size; i++) {

        if (ht->data_array[i] == NULL || ht->data_array[i] == &DELETED_ITEM)
            continue;

        char *old_key = ht->data_array[i]->key;

        unsigned long new_index = hash((unsigned char *)old_key) % new_size;

        // checking for collision
        if (new_array[new_index] != NULL) {
            // linear probing
            while (new_array[new_index] != NULL) {
                new_index = (new_index + 1) % new_size;
            }
        }

        new_array[new_index] = ht->data_array[i];
    }
    free(ht->data_array);
    ht->data_array = new_array;
    ht->size = new_size;
    return 0;
}

/*
 * Insert a new <key, pair> in the hash table.
 * If the key already exist, the value will be overwritten
 */
void insert(HashTable *ht, char *key, int data) {

    if (ht == NULL) {
        fprintf(stderr, "Error, the hash table has not been initialized");
        return;
    }

    if (key == NULL) {
        fprintf(stderr, "key cannot be null\n");
        return;
    }
    float load_factor = (float)ht->count / ht->size;
    // reallocating memory if needed
    if (load_factor >= REALLOCATION_THRESHOLD) {
        int rstatus = reallocate_table(ht);
        if (rstatus) {
            fprintf(stderr, "Error when reallocating memory\n");
            return;
        }
    }

    // getting the hash

    unsigned long new_index = hash((unsigned char *)key) % ht->size;
    unsigned long start_index = new_index;

    // checking for collision
    if (ht->data_array[new_index] != NULL &&
        ht->data_array[new_index] != &DELETED_ITEM) {
        // linear probing
        while (ht->data_array[new_index] != NULL &&
               ht->data_array[new_index] != &DELETED_ITEM) {
            // checking if the key already exist
            if (strcmp(ht->data_array[new_index]->key, key) == 0) {
                ht->data_array[new_index]->data = data;
                return;
            }

            new_index = (new_index + 1) % ht->size;
            if (new_index == start_index)
                break;
        }
    }

    // add the pair

    Pair *pair = malloc(sizeof(Pair));
    if (pair == NULL) {
        fprintf(stderr, "Error when allocating a new pair\n");
        return;
    }

    pair->data = data;
    pair->key = string_duplicate(key);

    ht->data_array[new_index] = pair;
    ht->count++;

    return;
}

/*
 * Prints the hash table
 */
void print(const HashTable *ht) {

    if (ht == NULL) {
        printf("Empty hash table\n");
    }

    printf("\nNumber of pairs: %zu over %zu total size, capacity: %.2f%%",
           ht->count, ht->size, ((float)ht->count / ht->size) * 100);

    printf("\nPairs:\n");

    for (size_t i = 0; i < ht->size; i++) {
        if (ht->data_array[i] != NULL && ht->data_array[i] != &DELETED_ITEM) {
            printf("\nPair: [%s] -> [%d]", ht->data_array[i]->key,
                   ht->data_array[i]->data);
        }
    }
    printf("\nEND\n");
}

/*
 * Returns 1 if the hash table has the input item 0 otherwise
 */
int has_item(const HashTable *ht, int data) {

    if (ht == NULL || ht->count == 0) {
        return 0;
    }

    for (size_t i = 0; i < ht->size; i++) {

        if (ht->data_array[i] == NULL || ht->data_array[i] == &DELETED_ITEM)
            continue;

        if (ht->data_array[i]->data == data)
            return 1;
    }
    return 0;
}

/*
 * Returns value at the corresponding key, if the key has no item associated
 * returns -1
 */
int get_item(const HashTable *ht, char *key) {

    if (ht == NULL || ht->count == 0) {
        return -1;
    }

    if (key == NULL) {
        fprintf(stderr, "The provided key is null. Returning -1\n");
        return -1;
    }

    unsigned long index = hash((unsigned char *)key) % ht->size;
    unsigned long start_index = index;
    // checking for collision
    if (ht->data_array[index] != NULL) {
        // linear probing
        while (ht->data_array[index] != NULL) {

            if (ht->data_array[index] != &DELETED_ITEM) {

                if (strcmp(ht->data_array[index]->key, key) == 0) {
                    return ht->data_array[index]->data;
                }
            }

            index = (index + 1) % ht->size;
            if (index == start_index)
                return -1;
        }
    }

    return -1;
}

/*
 * Delete from the table the correspinding item to the provided key
 */
void delete_item(HashTable *ht, char *key) {

    if (ht == NULL || ht->count == 0) {
        return;
    }

    if (key == NULL) {
        fprintf(stderr, "The provided key is null. Returning\n");
        return;
    }

    unsigned long index = hash((unsigned char *)key) % ht->size;
    unsigned long start_index = index;
    // checking for collision
    if (ht->data_array[index] != NULL) {
        // linear probing
        while (ht->data_array[index] != NULL) {

            if (ht->data_array[index] != &DELETED_ITEM) {
                if (strcmp(ht->data_array[index]->key, key) == 0) {

                    free(ht->data_array[index]->key);
                    free(ht->data_array[index]);
                    ht->data_array[index] = &DELETED_ITEM;
                    ht->count--;
                    return;
                }
            }

            index = (index + 1) % ht->size;
            if (index == start_index)
                return;
        }
    }
}
/*
 * Delete the hash table form the memory
 */
void destroy(HashTable *ht) {
    if (ht == NULL) {
        return;
    }

    if (ht->data_array != NULL) {

        for (size_t i = 0; i < ht->size; i++) {

            Pair *item = ht->data_array[i];

            if (item != NULL && item != &DELETED_ITEM) {

                free(ht->data_array[i]->key);

                free(item);
            }
        }
        free(ht->data_array);
    }

    // RIGHT NOW THE MAIN STRUCTURE IS IN THE STACK
    // free(ht);
}
