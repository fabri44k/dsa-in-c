#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

size_t get_parent_index(size_t index) {
    if (index == 0) {
        return 0;
    }
    return ((index - 1) / 2);
}

size_t get_left_child_index(size_t index) { return (2 * index + 1); }

size_t get_right_child_index(size_t index) { return (2 * index + 2); }

void max_heapify(int *array, size_t n, size_t start) {
    size_t curr = start;
    size_t left = get_left_child_index(curr);
    size_t right = get_right_child_index(curr);
    size_t largest;

    while (left < n) {

        // find the largest node
        largest = left;

        if (right < n && array[left] < array[right]) {
            largest = right;
        }

        if (array[curr] < array[largest]) {

            swap(&array[curr], &array[largest]);
            curr = largest;
        } else {
            break;
        }

        left = 2 * curr + 1;
        right = 2 * curr + 2;
    }
}

void heapsort(int *array, size_t len) {
    if (len <= 1)
        return;

    // create heap from array
    for (int i = (int)(len / 2 - 1); i >= 0; i--) {
        max_heapify(array, len, i);
    }

    // order
    for (size_t end = len - 1; end > 0; --end) {
        swap(&array[0], &array[end]);
        max_heapify(array, end, 0);
    }

    return;
}
