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

    // for (int i = 20; i > 3; --i) {
    //     insert(&h, i);
    // }

    int array[] = {20, 60, 5, 54, 17, 63, 85, 2, 69, 33};

    add_array_to_heap(&h, array, 10);

    print_heap(&h);

    printf("Max is %d\n", extract_max(&h));
    print_heap(&h);
    return 0;
}
