#include <stdio.h>
#include <stdlib.h>

void merge(int *, int *, int, int, int);
void merge_sort_bottom_up(int *, int);

int main(void) {
    int arr[] = {53, 4, 1, 2, 6, 23, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    merge_sort_bottom_up(arr, n);

    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

void merge(int *arr, int *temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left; i <= right; i++) arr[i] = temp[i];
}

void merge_sort_bottom_up(int *arr, int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    if (!temp) return;

    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - 1; left += 2 * size){
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? 
                        (left + 2 * size - 1) : (n - 1);
            if (mid < right) merge(arr, temp, left, mid, right);
        }
    }

    free(temp);
}