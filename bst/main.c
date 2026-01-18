#include "bst.h"
#include <stdio.h>

int main(void) {

    Bst bst;
    create(&bst);

    insert(&bst, 10);
    insert(&bst, 20);
    insert(&bst, 5);
    insert(&bst, 2);
    insert(&bst, 7);
    insert(&bst, 17);

    erase(&bst, 7);

    print(&bst);

    return 0;
}
