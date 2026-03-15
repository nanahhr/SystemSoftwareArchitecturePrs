#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    size_t max_size = SIZE_MAX;

    printf("Trying to allocate: %zu bytes (2^64 - 1)\n", max_size);

    void *ptr = malloc(max_size);

    if (ptr == NULL)
    {
        perror("malloc");
        printf("Result: malloc() returned NULL. Allocation failed.\n");
    }
    else
    {
        printf("Result: Successfully allocated at %p\n", ptr);
        free(ptr);
    }

    return 0;
}