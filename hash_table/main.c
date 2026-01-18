#include "hash_table.h"
#include <stdio.h>
#include <string.h>

int main(void) {

    HashTable ht;

    create(&ht, 3);

    char buf[100];
    strcpy(buf, "Mario");
    insert(&ht, buf, 1);

    strcpy(buf, "Luca");
    insert(&ht, buf, 2);

    print(&ht);

    destroy(&ht);

    return 0;
}
