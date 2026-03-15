#include <stdio.h>
#include <stdlib.h>

int main()
{
    void *ptr1 = realloc(NULL, 16);
    printf("realloc(NULL, 16) allocated at: %p\n", ptr1);

    void *ptr2 = realloc(ptr1, 0);
    printf("realloc(ptr, 0) returned: %p\n", ptr2);

    return 0;
}