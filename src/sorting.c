#include "sorting.h"
#include <stdlib.h>
#include <string.h>

static inline void swap(int *a, int *b, SortMetrics *metrics) {
    int temp = *a;
    *a = *b;
    *b = temp;
    metrics->swaps++;
}

// ============= BUBBLE SORT =============
void bubble_sort(int arr[], int n, SortMetrics *metrics) {
    metrics->comparisons = 0;
    metrics->swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            metrics->comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1], metrics);
            }
        }
    }
}

// ============= INSERTION SORT =============
void insertion_sort(int arr[], int n, SortMetrics *metrics) {
    metrics->comparisons = 0;
    metrics->swaps = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            metrics->comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                metrics->swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// ============= HEAP SORT =============
static void heapify(int arr[], int n, int i, SortMetrics *metrics) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        metrics->comparisons++;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        metrics->comparisons++;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest], metrics);
        heapify(arr, n, largest, metrics);
    }
}

void heap_sort(int arr[], int n, SortMetrics *metrics) {
    metrics->comparisons = 0;
    metrics->swaps = 0;

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, metrics);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i], metrics);
        heapify(arr, i, 0, metrics);
    }
}

// ============= MERGE SORT =============
static void merge(int arr[], int left, int mid, int right, SortMetrics *metrics) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        metrics->swaps++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        metrics->swaps++;
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        metrics->comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        metrics->swaps++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        metrics->swaps++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        metrics->swaps++;
        j++;
        k++;
    }

    free(L);
    free(R);
}

static void merge_sort_helper(int arr[], int left, int right, SortMetrics *metrics) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_helper(arr, left, mid, metrics);
        merge_sort_helper(arr, mid + 1, right, metrics);
        merge(arr, left, mid, right, metrics);
    }
}

void merge_sort(int arr[], int n, SortMetrics *metrics) {
    metrics->comparisons = 0;
    metrics->swaps = 0;
    if (n > 1) {
        merge_sort_helper(arr, 0, n - 1, metrics);
    }
}

// ============= QUICK SORT =============
static int partition(int arr[], int low, int high, SortMetrics *metrics) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        metrics->comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j], metrics);
        }
    }
    swap(&arr[i + 1], &arr[high], metrics);
    return i + 1;
}

static void quick_sort_helper(int arr[], int low, int high, SortMetrics *metrics) {
    if (low < high) {
        int pi = partition(arr, low, high, metrics);
        quick_sort_helper(arr, low, pi - 1, metrics);
        quick_sort_helper(arr, pi + 1, high, metrics);
    }
}

void quick_sort(int arr[], int n, SortMetrics *metrics) {
    metrics->comparisons = 0;
    metrics->swaps = 0;
    if (n > 1) {
        quick_sort_helper(arr, 0, n - 1, metrics);
    }
}

// ============= RADIX SORT =============
static int get_max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

static void counting_sort_by_digit(int arr[], int n, int exp, SortMetrics *metrics) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
        metrics->comparisons++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
        metrics->swaps++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        metrics->swaps++;
    }

    free(output);
}

void radix_sort(int arr[], int n, SortMetrics *metrics) {
    metrics->comparisons = 0;
    metrics->swaps = 0;

    if (n <= 0) return;

    int max = get_max(arr, n);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        counting_sort_by_digit(arr, n, exp, metrics);
    }
}
