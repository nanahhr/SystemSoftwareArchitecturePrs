#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    const char *filename = "experiment.tmp";
    const char *test_data = "Test data";
    char buffer[100];

    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }
    write(fd, test_data, strlen(test_data));

    lseek(fd, 0, SEEK_SET);

    printf("Data in file: '%s' (%zu bytes)\n", test_data, strlen(test_data));
    printf("Requested bytes: 100\n");

    ssize_t bytes_read = read(fd, buffer, 100);

    if (bytes_read >= 0)
    {
        buffer[bytes_read] = '\0';
        printf("Actual bytes read: %zd\n", bytes_read);
        printf("Status: %s\n", (bytes_read < 100) ? "Short read occurred (EOF)" : "Full read");
    }
    else
    {
        perror("Read failed");
    }

    close(fd);
    unlink(filename);
    return 0;
}