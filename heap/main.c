#include "heap.h"
#include <stdio.h>

int main(void) {

    heap h;
    create_heap(&h);

    printf("Is empty %d\n", is_empty(&h));

    // print_heap(&h);

    insert(&h, 1);
    insert(&h, 3);
    insert(&h, 2);

    for (int i = 20; i > 3; --i) {
        insert(&h, i);
    }

    print_heap(&h);

    printf("Max is %d\n", extract_max(&h));
    print_heap(&h);
    return 0;
}
