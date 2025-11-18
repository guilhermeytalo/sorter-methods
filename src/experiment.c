#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorting.h"

#define NUM_TRIALS 30
#define MAX_SIZE 1000
#define STEP_SIZE 10

typedef void (*SortFunction)(int[], int, SortMetrics*);

typedef struct {
    const char *name;
    SortFunction function;
} Algorithm;

void generate_random_array(int arr[], int n, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

void run_experiment(Algorithm algo, int size, FILE *output) {
    uint64_t total_comparisons = 0;
    uint64_t total_swaps = 0;

    for (int trial = 0; trial < NUM_TRIALS; trial++) {
        int *arr = (int *)malloc(size * sizeof(int));
        generate_random_array(arr, size, time(NULL) + trial);

        SortMetrics metrics;
        algo.function(arr, size, &metrics);

        total_comparisons += metrics.comparisons;
        total_swaps += metrics.swaps;

        free(arr);
    }

    double avg_comparisons = (double)total_comparisons / NUM_TRIALS;
    double avg_swaps = (double)total_swaps / NUM_TRIALS;

    fprintf(output, "    {\n");
    fprintf(output, "      \"size\": %d,\n", size);
    fprintf(output, "      \"algorithm\": \"%s\",\n", algo.name);
    fprintf(output, "      \"comparisons\": %.2f,\n", avg_comparisons);
    fprintf(output, "      \"swaps\": %.2f\n", avg_swaps);
    fprintf(output, "    }");
}

int main() {
    Algorithm algorithms[] = {
        {"Bubble Sort", bubble_sort},
        {"Insertion Sort", insertion_sort},
        {"Heap Sort", heap_sort},
        {"Merge Sort", merge_sort},
        {"Quick Sort", quick_sort},
        {"Radix Sort", radix_sort}
    };

    int num_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);

    FILE *output = fopen("results/data.json", "w");
    if (!output) {
        fprintf(stderr, "Error: Could not create output file\n");
        return 1;
    }

    fprintf(output, "{\n");
    fprintf(output, "  \"metadata\": {\n");
    fprintf(output, "    \"trials\": %d,\n", NUM_TRIALS);
    fprintf(output, "    \"maxSize\": %d,\n", MAX_SIZE);
    fprintf(output, "    \"stepSize\": %d\n", STEP_SIZE);
    fprintf(output, "  },\n");
    fprintf(output, "  \"results\": [\n");

    printf("Running sorting algorithm analysis...\n");
    printf("Trials per size: %d\n", NUM_TRIALS);
    printf("Array sizes: 1 to %d (step: %d)\n\n", MAX_SIZE, STEP_SIZE);

    int total_experiments = 0;
    int completed_experiments = 0;

    for (int size = 1; size <= MAX_SIZE; size += STEP_SIZE) {
        total_experiments += num_algorithms;
    }
    if (MAX_SIZE % STEP_SIZE != 0) {
        total_experiments += num_algorithms;
    }

    int first = 1;
    for (int size = 1; size <= MAX_SIZE; size += STEP_SIZE) {
        for (int i = 0; i < num_algorithms; i++) {
            if (!first) {
                fprintf(output, ",\n");
            }
            first = 0;

            run_experiment(algorithms[i], size, output);
            completed_experiments++;

            printf("\rProgress: %d/%d (%.1f%%) - Size: %d, Algorithm: %s",
                   completed_experiments, total_experiments,
                   (completed_experiments * 100.0) / total_experiments,
                   size, algorithms[i].name);
            fflush(stdout);
        }
    }

    if (MAX_SIZE % STEP_SIZE != 0) {
        for (int i = 0; i < num_algorithms; i++) {
            fprintf(output, ",\n");
            run_experiment(algorithms[i], MAX_SIZE, output);
            completed_experiments++;

            printf("\rProgress: %d/%d (%.1f%%) - Size: %d, Algorithm: %s",
                   completed_experiments, total_experiments,
                   (completed_experiments * 100.0) / total_experiments,
                   MAX_SIZE, algorithms[i].name);
            fflush(stdout);
        }
    }

    fprintf(output, "\n  ]\n");
    fprintf(output, "}\n");

    fclose(output);

    printf("\n\nExperiment complete!\n");
    printf("Results saved to: results/data.json\n");

    return 0;
}
