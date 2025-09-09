#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *, int, int);
void selection_sort(int *, int, int);
void insertion_sort(int *, int, int);
void merge_sort(int *, int, int);
void merge(int *, int, int, int);
void swap(int *, int *);
int partition(int *, int, int);
void quick_sort(int *, int, int);
int get_max(int *, int);
void counting_sort(int *, int, int);
void radix_sort(int *, int);
void shell_sort(int *, int);
void heapify(int *, int, int);
void heap_sort(int *, int);
void bucket_insertion(int *, int);
void bucket_sort(int *, int);
void radix_exchange_sort(int *, int, int, int);
int get_max_bit(int *, int);
void address_cal_insertion(int *, int);
void address_cal_sort(int *, int);

int main(void){
    int arr[] = {9, 4, 1, 2, 6, 8, 0};
    int len = sizeof(arr) / sizeof(*arr);

    printf("Before sorting\n");
    for(int i=0; i<len; i++) printf("%d ", arr[i]);
    printf("\n");

    bubble_sort(arr, 0, len-1);
    selection_sort(arr, 0, len-1);
    insertion_sort(arr, 0, len-1);
    merge_sort(arr, 0, len-1);
    quick_sort(arr, 0, len-1);
    radix_sort(arr, len);
    counting_sort(arr, len, 0);
    shell_sort(arr, len);
    heap_sort(arr, len);
    bucket_sort(arr, len);
    radix_exchange_sort(arr, 0, len-1, 3);
    address_cal_sort(arr, len);

    printf("\nAfter sorting\n");
    for(int i=0; i<len; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

void insertion_sort(int *arr, int left, int right){
    int temp, j;

    for(int i=left+1; i<=right; i++){
        temp = arr[i];
        j = i - 1;

        while(j >= left && arr[j] > temp){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

void selection_sort(int *arr, int left, int right){
    int ind, temp;

    for(int i=left; i<=right-1; i++){
        ind = i;
        for(int j=i+1; j<=right; j++){
            if(arr[j] < arr[ind]) ind = j;
        }

        if(ind != i){
            temp = arr[i];
            arr[i] = arr[ind];
            arr[ind] = temp;
        }
    }
}

void bubble_sort(int *arr, int left, int right){
    int count, temp;

    for(int i=left; i<=right-1; i++){
        count = 0;
        for(int j=left; j<right-i; j++){
            if(arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                count++;
            }
        }
        if(count == 0) break;
    }
}

void merge(int *arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i=0; i<n1; i++)
        L[i] = arr[left+i];
    for (int j=0; j<n2; j++)
        R[j] = arr[mid+1+j];

    int i = 0, j = 0, k = left;

    while (i<n1 && j<n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void merge_sort(int *arr, int left, int right){
    if(left < right){
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++){
        if(arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int *arr, int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int get_max(int *arr, int n) {
    int max = arr[0];
    for(int i=1; i<n; i++)
        if(arr[i] > max)
            max = arr[i];
    return max;
}

void counting_sort(int *arr, int n, int exp) {
    int max = arr[0], min = arr[0];

    if(exp == 0){
        for (int i=1; i<n; i++) {
            if(arr[i] > max) max = arr[i];
            if(arr[i] < min) min = arr[i];
        }
    }
    else{
        min = 0;
        max = 9;
    }

    int range = max - min + 1;
    int *count = (int *)calloc(range, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    for(int i=0; i<n; i++) {
        int key = (exp == 0) ? (arr[i] - min) : (arr[i] / exp) % 10;
        count[key]++;
    }

    for(int i=1; i<range; i++)
        count[i] += count[i - 1];

    for (int i=n-1; i>=0; i--) {
        int key = (exp == 0) ? (arr[i] - min) : (arr[i] / exp) % 10;
        output[count[key] - 1] = arr[i];
        count[key]--;
    }

    for(int i=0; i<n; i++)
        arr[i] = output[i];

    free(count);
    free(output);
}

void radix_sort(int *arr, int n) {
    int max = get_max(arr, n);

    for(int exp=1; max/exp>0; exp*=10)
        counting_sort(arr, n, exp);
}

void shell_sort(int *arr, int n){
    for(int gap=n/2; gap>0; gap/=2){
        for(int i=gap; i<n; i++){
            int temp = arr[i];
            int j = i;

            while (j>=gap && arr[j-gap]>temp) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void heapify(int *arr, int n, int i){
    int largest = i, l = 2*i+1, r = 2*i+2;

    if(l<n && arr[l]>arr[largest]) largest = l;
    if(r<n && arr[r]>arr[largest]) largest = r;
    if(largest != i){
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heap_sort(int *arr, int n) {
    for(int i=n/2-1; i>=0; i--) heapify(arr, n, i);
    for(int i=n-1; i>0; i--){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void bucket_insertion(int *arr, int n) {
    for (int i=1; i<n; i++) {
        int key = arr[i], j = i-1;
        while (j>=0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void bucket_sort(int *arr, int n) {
    int max = arr[0];
    for (int i=1; i<n; i++)
        if (arr[i] > max) max = arr[i];

    int bucket_count = n;
    int **buckets = (int **)malloc(bucket_count * sizeof(int *));
    int *count = (int *)calloc(bucket_count, sizeof(int));

    for (int i=0; i<bucket_count; i++)
        buckets[i] = (int *)malloc(n * sizeof(int));

    for (int i=0; i<n; i++) {
        int bi = (arr[i] * bucket_count) / (max+1); 
        buckets[bi][count[bi]++] = arr[i];
    }

    for (int i=0; i<bucket_count; i++)
        bucket_insertion(buckets[i], count[i]);

    int idx = 0;
    for (int i=0; i<bucket_count; i++)
        for (int j=0; j<count[i]; j++)
            arr[idx++] = buckets[i][j];

    for (int i=0; i<bucket_count; i++)
        free(buckets[i]);
    free(buckets);
    free(count);
}

void radix_exchange_sort(int *arr, int left, int right, int bit) {
    if (left >= right || bit < 0) return;
    int i = left, j = right;
    while (i <= j) {
        while (i <= j && ((arr[i] >> bit) & 1) == 0) i++;
        while (i <= j && ((arr[j] >> bit) & 1) == 1) j--;
        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    radix_exchange_sort(arr, left, j, bit-1);
    radix_exchange_sort(arr, i, right, bit-1);
}

int get_max_bit(int *arr, int n) {
    int max = arr[0];
    for (int i=1; i<n; i++) if (arr[i] > max) max = arr[i];
    if (max == 0) return 0;
    int bit = 0;
    while (max > 0) { bit++; max >>= 1; }
    return bit-1;
}

void address_cal_insertion(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void address_cal_sort(int *arr, int n) {
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    int range = max - min + 1;
    int bucket_count = n;

    int **buckets = (int **)malloc(bucket_count * sizeof(int *));
    int *count = (int *)calloc(bucket_count, sizeof(int));
    for (int i = 0; i < bucket_count; i++)
        buckets[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int addr = ((arr[i] - min) * bucket_count) / range;
        if (addr >= bucket_count) addr = bucket_count - 1; 
        buckets[addr][count[addr]++] = arr[i];
    }

    for (int i = 0; i < bucket_count; i++)
        if (count[i] > 1) address_cal_insertion(buckets[i], count[i]);

    int idx = 0;
    for (int i = 0; i < bucket_count; i++)
        for (int j = 0; j < count[i]; j++)
            arr[idx++] = buckets[i][j];

    for (int i = 0; i < bucket_count; i++) free(buckets[i]);
    free(buckets);
    free(count);
}