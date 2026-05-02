#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int compare_ints(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

double measure_qsort(int *array, size_t n)
{
    clock_t start = clock();
    qsort(array, n, sizeof(int), compare_ints);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

void run_experiments(size_t size)
{
    int *arr = malloc(size * sizeof(int));

    printf("--- Experimenting with %zu elements ---\n", size);

    for (size_t i = 0; i < size; i++)
        arr[i] = rand();
    printf("Random data:     %f sec\n", measure_qsort(arr, size));

    for (size_t i = 0; i < size; i++)
        arr[i] = i;
    printf("Sorted data:     %f sec\n", measure_qsort(arr, size));

    for (size_t i = 0; i < size; i++)
        arr[i] = size - i;
    printf("Reverse sorted:  %f sec\n", measure_qsort(arr, size));

    for (size_t i = 0; i < size; i++)
        arr[i] = 42;
    printf("Identical data:  %f sec\n", measure_qsort(arr, size));

    free(arr);
}

void run_tests()
{
    printf("\n--- Tests ---\n");
    int test_arr[] = {9, 1, 5, 2, 7, 3};
    size_t n = sizeof(test_arr) / sizeof(test_arr[0]);

    qsort(test_arr, n, sizeof(int), compare_ints);

    int passed = 1;
    for (size_t i = 0; i < n - 1; i++)
    {
        if (test_arr[i] > test_arr[i + 1])
            passed = 0;
    }

    if (passed)
        printf("Test Passed: Array is correctly sorted.\n");
    else
        printf("Test Failed: Sorting error detected.\n");
}

int main()
{
    srand(time(NULL));
    run_experiments(50000);
    run_tests();
    return 0;
}