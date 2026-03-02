#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    int count = 0;

    printf("Starting process creation test (ulimit -u)...\n");

    while (1)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            printf("\nReached limit at %d processes.\n", count);
            perror("Fork failed");
            break;
        }
        else if (pid == 0)
        {
            sleep(10);
            exit(0);
        }
        else
        {
            count++;
            if (count % 10 == 0)
            {
                printf("Processes created: %d\n", count);
            }
        }
    }
    return 0;
}