#include "queue.h"
#include <stdio.h>

int main(void){

    Queue q;

    create(&q);

    enqueue(&q, 1);
    
    dequeue(&q);
    
    dequeue(&q);

    enqueue(&q, 2);

    enqueue(&q, 3);



    printf("First element is %d\n", front(&q));

    print(&q);

    return 0;
}
