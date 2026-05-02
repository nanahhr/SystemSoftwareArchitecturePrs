#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main()
{
    const char *filename = "test_write.tmp";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *data = "Testing text";
    size_t nbytes = strlen(data);

    ssize_t count = write(fd, data, nbytes);

    printf("Requested bytes: %zu\n", nbytes);
    printf("Actual written bytes: %zd\n", count);

    if (count == -1)
    {
        printf("Status: Write failed (errno: %d)\n", errno);
    }
    else if ((size_t)count < nbytes)
    {
        printf("Status: Partial write occurred!\n");
    }
    else
    {
        printf("Status: Full write successful.\n");
    }

    close(fd);
    unlink(filename);
    return EXIT_SUCCESS;
}