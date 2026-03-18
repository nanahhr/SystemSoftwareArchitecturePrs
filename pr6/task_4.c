#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MEM_SIZE (200 * 1024 * 1024)

int main()
{
    char *arr = malloc(MEM_SIZE);
    if (arr == NULL)
    {
        perror("malloc failed");
        return 1;
    }

    memset(arr, 0, MEM_SIZE);
    printf("Memory allocated and initialized. Parent PID: %d\n", getpid());

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child process writing to memory...\n");
        memset(arr, 1, MEM_SIZE / 2);
        printf("Child process finished writing.\n");
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("Parent process: child finished.\n");
    }

    free(arr);
    return 0;
}