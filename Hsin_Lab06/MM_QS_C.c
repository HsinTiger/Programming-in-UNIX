#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100000

// swap function to swap two elements
void swap(long *a, long *b) {
    long temp = *a;
    *a = *b;
    *b = temp;
}

// Median of Medians algorithm to find the pivot element
long median_of_medians(long *numbers, int n) {
    if (n <= 5) {
        // if the array size is 5 or less, we can just sort it and return the middle element
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (numbers[i] > numbers[j]) {
                    swap(&numbers[i], &numbers[j]);
                }
            }
        }
        return numbers[n / 2];
    }

    // divide the array into subarrays of size 5
    int num_groups = n / 5;
    if (n % 5 != 0) {
        num_groups++;
    }
    long medians[num_groups];
    int start = 0;
    for (int i = 0; i < num_groups; i++) {
        int end = start + 4;
        if (end >= n) {
            end = n - 1;
        }
        medians[i] = median_of_medians(numbers + start, end - start + 1);
        start += 5;
    }

    // recursively find the median of medians
    return median_of_medians(medians, num_groups);
}

// quicksort implementation with median of medians pivot
void quicksort_median(long *numbers, int left, int right) {
    if (left >= right) {
        // base case: array is sorted
        return;
    }

    // find the pivot using median of medians
    long pivot = median_of_medians(numbers + left, right - left + 1);

    // partition the array around the pivot
    int i = left;
    int j = right;
    while (i <= j) {
        while (numbers[i] < pivot) {
            i++;
        }
        while (numbers[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(&numbers[i], &numbers[j]);
            i++;
            j--;
        }
    }

    // recursively sort the left and right subarrays
    quicksort_median(numbers, left, j);
    quicksort_median(numbers, i, right);
}

// wrapper function to use with function pointer typedef
void quicksort_median_wrapper(long *numbers, int n) {
    quicksort_median(numbers, 0, n - 1);
}

// test program to demonstrate the quicksort with median of medians implementation
int main() {
    long numbers[MAX_SIZE];
    int n;

    // get input
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%ld", &numbers[i]);
    }

    // sort the array using quicksort with median of medians pivot
    sort_funcptr_t sort_func = quicksort_median_wrapper;
    sort_func(numbers, n);
    return 0;
}
