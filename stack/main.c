# include <stdio.h>
#include "stack.h"

int main(void)
{
    
    Stack s;

    create(&s);


    for (int i = 1; i < 11; i++){
        push(&s, i);
    }

    print(&s);

    pop(&s);
    pop(&s);
    pop(&s);
    pop(&s);
    pop(&s);
    
    print(&s);

    printf("The last element is %d", peek(&s));

    return 0;
}
