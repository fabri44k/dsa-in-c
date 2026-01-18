#include "list.h"
#include <stdio.h>

int main(void) {

    List l;

    create(&l);

    // for (int i = 1; i < 100001; i++) {
    //     insert(&l, i - 1, i);
    // }

    append(&l, 1);
    append(&l, 2);
    append(&l, 3);

    reverse(&l);

    print(&l);
    return 0;
}
