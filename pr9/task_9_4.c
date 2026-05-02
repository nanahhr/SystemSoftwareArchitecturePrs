#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("1. Executing 'whoami':\n");
    printf("Output: ");
    fflush(stdout);
    system("whoami");

    printf("\n");

    printf("2. Executing 'id' to see full account details and groups:\n");
    system("id");

    printf("\nEnd\n");

    return 0;
}