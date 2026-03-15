#include <stdio.h>
#include <stdlib.h>

int main()
{
    void *ptr = malloc(32);
    printf("Allocated at: %p\n", ptr);

    free(ptr);
    free(ptr);

    void *a = malloc(32);
    void *b = malloc(32);

    printf("First allocation: %p\n", a);
    printf("Second allocation: %p\n", b);

    if (a == b)
    {
        printf("Double free detected: tcache loop created!\n");
    }

    return 0;
}