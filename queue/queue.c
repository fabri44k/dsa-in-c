#include <stdio.h>
#include <stdlib.h>
# include "queue.h"

/*
* Initalize the queue
*/
void create(Queue * q){

    if (q == NULL){
        fprintf(stderr, "Queue is NULL.\n");
        return;
    }

    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
}

/*
* Enqueue operand
*/
void enqueue(Queue * q, int data){

    if (q == NULL){
        fprintf(stderr, "Queue has not been initalized.\n");
        return;
    }

    Elem * e = malloc(sizeof(Elem));
    if (e == NULL){
        fprintf(stderr, "Error when allocating memory\n");
        return;
    }

    e->data = data;
    e->next = NULL;
   

    if (q->head == NULL){
        q->head = e;
    } else {
        q->tail->next = e;
    }

    q->tail = e;
    q->count++;


}

/*
 * Dequeue operator
 */
int dequeue(Queue * q){
    
    if (q == NULL){
        fprintf(stderr, "Queue has not been initalized. Returning -1\n");
        return -1;
    }

    if (q->tail == NULL){
        printf("Empty Queue, unable to dequeue, returning -1\n");
        return -1;
    }

    int result = q->head->data;
    Elem * next = q->head->next;
    
    free(q->head);


    q->head = next;
    if(q->head == NULL){
        q->tail = NULL;
    }
    q->count--;

    return result;
    

}

/*
 * Return the numer of elementes
 */
int get_length(const Queue * q){
    if (q == NULL){
        return 0;
    }

    return q->count;
}


/*
 * Returns 1 if the queue has no element, 0 otherwise
 * */
int is_empty(const Queue * q){

    if (q == NULL)
        return 1;

    return (q->head == NULL);

}

/*
 * Prints the queue
*/
void print(const Queue * q){
    

    if (q == NULL || is_empty(q)) {
        fprintf(stderr, "\nEmpty Queue, unable to print\n");
        return;
    }

    Elem * current = q->head;

    while(current != NULL){

        printf("-> [ %d ] ", current->data);
        current = current->next;
    }
    printf("\n");

}

/*
 * Get the first element without removing
 */
int front(const Queue * q){
    
    if (q == NULL){
        fprintf(stderr, "Queue has not been initalized. Returning -1 \n");
        return -1;
    }

    if (q->tail == NULL){
        printf("Empty Queue, returning -1");
        return -1;
    }

    int result = q->head->data;
    return result;
}
