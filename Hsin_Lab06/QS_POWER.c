#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

#define MIN_SIZE 16

void quicksort(long *numbers, int n) {
    int i = 0, j = n - 1;
    long pivot, temp;
    if (n < MIN_SIZE) {
        // Insertion sort for small arrays
        for (int i = 1; i < n; ++i) {
            temp = numbers[i];
            j = i - 1;
            while (j >= 0 && numbers[j] > temp) {
                numbers[j + 1] = numbers[j];
                --j;
            }
            numbers[j + 1] = temp;
        }
        return;
    }
    // Select pivot
    pivot = numbers[n/2];
    // Partition the array
    while (i < j) {
        while (numbers[i] < pivot) ++i;
        while (numbers[j] > pivot) --j;
        if (i < j) {
            temp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = temp;
            ++i;
            --j;
        }
    }
    // Recursively sort the two partitions
    #pragma omp task
    quicksort(numbers, j + 1);
    #pragma omp task
    quicksort(numbers + i, n - i);
    #pragma omp taskwait
}

void main() {
    long numbers[] = {5, 2, 9, 1, 5, 6, -3,-100};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    #pragma omp parallel
    {
        #pragma omp single nowait
        quicksort(numbers, n);
    }
    for (int i = 0; i < n; ++i) {
        printf("%ld\n", numbers[i]);
    }
    return;
}
