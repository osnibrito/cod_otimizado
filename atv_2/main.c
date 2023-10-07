/**
 * Algorithms used:
 * 
 * Algorithm | Best Case | Average Case | Worst Case
 * ----------|-----------|--------------|-----------
 * MergeSort | O(nlogn)  | O(nlogn)     | O(nlogn)
 * QuickSort | O(nlogn)  | O(nlogn)     | O(nlogn)
 * HeapSort  | O(nlogn)  | O(nlogn)     | O(n^2)
*/

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000
#define RAND_SEED 1
#define MAX_VALUE 1000000

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)
#define LARGEST_CACHE_SZ (4 * MB)

// Remove data from processor caches
static unsigned char dummy_buffer[LARGEST_CACHE_SZ];
void clean_cache() {
    unsigned long long i;
    for (i = 0; i < LARGEST_CACHE_SZ; i++) dummy_buffer[i] += 1;
}

// Utils
void fill_array(int* arr) {
    srand(RAND_SEED);  // Always generate the same exact array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % MAX_VALUE;
    }
}

void print_array(int* arr) {
    srand(RAND_SEED);
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d", arr[i]);
        if (i != ARRAY_SIZE - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Sort functions

// Merge two sorted partitions of the array (l to m, m to r)
void _merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// MergeSort helper function
void _mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        _mergeSort(arr, l, m);
        _mergeSort(arr, m + 1, r);
        _merge(arr, l, m, r);
    }
}

// Merge sort main function
void mergeSort(int* arr) { _mergeSort(arr, 0, ARRAY_SIZE - 1); }

// Quick sort partitioning
int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and arr[high] (or pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// QuickSort helper
void _quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        _quickSort(arr, low, pi - 1);
        _quickSort(arr, pi + 1, high);
    }
}

// QuickSort main function
void quickSort(int* arr) { _quickSort(arr, 0, ARRAY_SIZE - 1); }

// Heap Sort
void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        // Swap arr[i] and arr[largest]
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

// Heap sort main function
void heapSort(int* arr) {
    for (int i = ARRAY_SIZE / 2 - 1; i >= 0; i--) {
        heapify(arr, ARRAY_SIZE, i);
    }

    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        // Swap arr[0] and arr[i]
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main(int argc, char** argv) {
    int* arr = malloc(ARRAY_SIZE * sizeof(int));

    fill_array(arr);
    clean_cache();
    mergeSort(arr);

    fill_array(arr);
    clean_cache();
    quickSort(arr);

    fill_array(arr);
    clean_cache();
    heapSort(arr);

    free(arr);

    return 0;
}