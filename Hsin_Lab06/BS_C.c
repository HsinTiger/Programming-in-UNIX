#include <stdio.h>

typedef void (*sort_funcptr_t)(long *numbers, int n);

void bubble_sort(long *numbers, int n) {
    int i, j;
    long temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (numbers[j] > numbers[j+1]) {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }
}

int main() {
    long arr[] = {64, 34, 25, -7,12, 22, 11, 90,-111};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Declare a function pointer of type `sort_funcptr_t`
    sort_funcptr_t sort_func = bubble_sort;

    // Call the sort function through the function pointer
    sort_func(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%ld ", arr[i]);
    }
    return 0;
}
