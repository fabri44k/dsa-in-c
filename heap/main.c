#include "heap.h"
#include <stdio.h>

int main(void) {

    heap h;
    create_heap(&h);

    printf("Is empty %d\n", is_empty(&h));

    return 0;
}
