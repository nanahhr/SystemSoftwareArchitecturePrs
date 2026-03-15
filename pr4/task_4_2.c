#include <stdio.h>
#include <stdlib.h>

int main()
{
    int neg = -1;
    printf("Attempting malloc(-1)...\n");
    void *ptr1 = malloc(neg);
    if (ptr1 == NULL)
        printf("malloc(-1) failed.\n");
    else
    {
        printf("malloc(-1) allocated memory.\n");
        free(ptr1);
    }

    int xa = 1000000;
    int xb = 1000000;
    int num = xa * xb;

    printf("\nCalculating size: %d * %d = %d (overflowed)\n", xa, xb, num);
    void *ptr2 = malloc(num);

    if (ptr2 == NULL)
        printf("malloc(num) failed.\n");
    else
    {
        printf("malloc(num) allocated %d bytes.\n", num);
        free(ptr2);
    }

    return 0;
}