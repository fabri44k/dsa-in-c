#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// import sorting alg
#include "heapsort.h"

// array size
#define N 1000000

int is_ordered(int *);

int main(void) {
    struct timeval start, stop;
    double secs = 0;

    int array[N];
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 1000;
    }

    printf("[START] Start sorting \n");
    gettimeofday(&start, NULL);

    // call the sorting algorithm being tested
    heapsort(array, N);

    printf("[END] End sorting\n");
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 +
           (double)(stop.tv_sec - start.tv_sec);
    printf("Time taken %f\n", secs);

    // printf("Printing result...\n");
    // printf("[");
    // for (size_t i = 0; i < N; ++i) {
    //     printf(" %d ,", array[i]);
    // }
    // printf("]\n");

    printf("Is ordered: %d\n", is_ordered(array));

    return 0;
}

int is_ordered(int *array) {

    int a = array[0];

    for (size_t i = 1; i < N; ++i) {
        if (a > array[i]) {
            return 0;
        }
        a = array[i];
    }
    return 1;
}
