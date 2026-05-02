#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    const char *filename = "sequence.tmp";
    unsigned char initial_data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error creating file");
        return EXIT_FAILURE;
    }
    write(fd, initial_data, sizeof(initial_data));

    if (lseek(fd, 3, SEEK_SET) == -1)
    {
        perror("Error calling lseek");
        close(fd);
        return EXIT_FAILURE;
    }

    ssize_t bytes_read = read(fd, buffer, 4);
    if (bytes_read == -1)
    {
        perror("Error reading file");
    }
    else
    {
        printf("Requested offset: 3\n");
        printf("Bytes read: %zd\n", bytes_read);
        printf("Buffer content: ");
        for (int i = 0; i < bytes_read; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    }

    close(fd);
    unlink(filename);
    return EXIT_SUCCESS;
}