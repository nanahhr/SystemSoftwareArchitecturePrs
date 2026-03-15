#include <stdio.h>
#include <stdlib.h>

int main()
{
    for (int i = 0; i < 2; i++)
    {
        void *ptr = malloc(10);
        if (!ptr)
            return 1;

        printf("Used memory at %p\n", ptr);
        free(ptr);
        ptr = NULL;
    }
    return 0;
}