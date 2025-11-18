#ifndef SORTING_H
#define SORTING_H

#include <stdint.h>

typedef struct {
    uint64_t comparisons;
    uint64_t swaps;
} SortMetrics;

void bubble_sort(int arr[], int n, SortMetrics *metrics);
void insertion_sort(int arr[], int n, SortMetrics *metrics);
void heap_sort(int arr[], int n, SortMetrics *metrics);
void merge_sort(int arr[], int n, SortMetrics *metrics);
void quick_sort(int arr[], int n, SortMetrics *metrics);
void radix_sort(int arr[], int n, SortMetrics *metrics);

#endif
