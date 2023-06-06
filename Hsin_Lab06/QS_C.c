#include <stdio.h>

void quicksort(long *numbers, int n) {
    int i, j;
    long pivot, temp;
    if (n < 2) {
        return;
    }
    pivot = numbers[n/2];
    for (i = 0, j = n - 1; ; i++, j--) {
        while (numbers[i] < pivot) {
            i++;
        }
        while (numbers[j] > pivot) {
            j--;
        }
        if (i >= j) {
            break;
        }
        temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
    quicksort(numbers, i);
    quicksort(numbers + i, n - i);
}

void main(){
    void (*sort_funcptr_t)(long *numbers, int n) = quicksort;
    long numbers[] = {5, 2, 9, 1, 5, 6, -3,-100};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    sort_funcptr_t(numbers, n);
    for(int i=0;i<n;i++)
        printf("%ld\n",numbers[i]);
    return;
}
