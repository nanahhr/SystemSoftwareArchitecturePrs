#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t sizes[] = {16, 1024, 65536};
    int iterations = 1000;

    for (int s = 0; s < 3; s++)
    {
        size_t size = sizes[s];
        int matches = 0;
        printf("Testing size: %zu bytes\n", size);

        for (int i = 0; i < iterations; i++)
        {
            void *addr1 = malloc(size);
            free(addr1);

            void *addr2 = malloc(size);
            if (addr2 == addr1)
            {
                matches++;
            }
            free(addr2);
        }
        printf("Reuse frequency: %.2f%%\n", (float)matches / iterations * 100);
    }
    return 0;
}