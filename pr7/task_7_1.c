#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *pipe_ptr;

    pipe_ptr = popen("who | more", "w");

    if (pipe_ptr == NULL)
    {
        perror("popen failed");
        return EXIT_FAILURE;
    }
    int status = pclose(pipe_ptr);

    if (status == -1)
    {
        perror("pclose failed");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}