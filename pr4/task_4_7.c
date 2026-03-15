#include <stdio.h>
#include <stdlib.h>

struct sbar
{
    int id;
    char data[100];
};

int main()
{
    struct sbar *ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr)
        return 1;

    struct sbar *newptr = reallocarray(ptr, 500, sizeof(struct sbar));

    if (newptr == NULL)
    {
        perror("reallocarray failed");
        free(ptr);
    }
    else
    {
        printf("Successfully reallocated to 500 elements.\n");
        ptr = newptr;
        free(ptr);
    }
    return 0;
}