#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    void *ptr = malloc(1024);
    printf("Initial pointer: %p\n", ptr);

    void *new_ptr = realloc(ptr, SIZE_MAX);

    if (new_ptr == NULL)
    {
        printf("realloc failed! Old pointer %p is still valid.\n", ptr);
        free(ptr);
    }
    else
    {
        free(new_ptr);
    }
    return 0;
}