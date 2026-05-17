#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    const char *filename = "output.txt";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    printf("File '%s' opened successfully before fork().\n", filename);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        close(fd);
        return EXIT_FAILURE;
    }
    else if (pid == 0)
    {
        const char *child_msg = "This is a Child process! (PID: %d)\n";
        char buf[128];
        int len = sprintf(buf, child_msg, getpid());

        if (write(fd, buf, len) < 0)
        {
            perror("Child write failed");
        }

        printf("Child process completed writing.\n");
        close(fd);
        return EXIT_SUCCESS;
    }
    else
    {
        sleep(1);

        const char *parent_msg = "This is a Parent Process! (PID: %d)\n";
        char buf[128];
        int len = sprintf(buf, parent_msg, getpid());

        if (write(fd, buf, len) < 0)
        {
            perror("Parent write failed");
        }

        printf("Parent process completed writing.\n");

        wait(NULL);
        close(fd);
    }

    return EXIT_SUCCESS;
}