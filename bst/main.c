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
    insert(&bst, 16);
    insert(&bst, 22);
    insert(&bst, 18);
    insert(&bst, 30);
    // delete_node(&bst, 10);

    printf("Predecessor of %d is %d\n", bst.root->left->data,
           (predecessor(bst.root->left)->data));
    printf("Successor of %d is %d\n", bst.root->data,
           (successor(bst.root)->data));
    print(&bst);
    destroy_tree(&bst);
    print(&bst);

    return 0;
}
