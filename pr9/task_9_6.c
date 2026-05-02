#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void try_access(const char *path)
{
    printf("\nTesting: %s \n", path);

    char cmd[256];
    sprintf(cmd, "ls -ld %s", path);
    system(cmd);

    int fd = open(path, O_RDONLY);
    if (fd != -1)
    {
        printf("Read attempt:  SUCCESS\n");
        close(fd);
    }
    else
    {
        printf("Read attempt:  FAILED (%s)\n", strerror(errno));
    }

    fd = open(path, O_WRONLY);
    if (fd != -1)
    {
        printf("Write attempt: SUCCESS\n");
        close(fd);
    }
    else
    {
        printf("Write attempt: FAILED (%s)\n", strerror(errno));
    }

    if (access(path, X_OK) == 0)
    {
        printf("Exec attempt:  ALLOWED\n");
    }
    else
    {
        printf("Exec attempt:  DENIED\n");
    }
}

int main()
{
    try_access(".");
    try_access("/usr/bin/ls");
    try_access("/etc/shadow");
    return 0;
}