#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void handle_sigxfsz(int sig)
{
    printf("\nFile size limit exceeded (SIGXFSZ)\n");
    exit(1);
}

int main(int argc, char *argv[])
{
    signal(SIGXFSZ, handle_sigxfsz);

    if (argc != 3)
    {
        printf("Program need two arguments\n");
        return 1;
    }

    int src = open(argv[1], O_RDONLY);
    if (src == -1)
    {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    // Відкриття файлу для запису
    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest == -1)
    {
        printf("Cannot open file %s for writing\n", argv[2]);
        close(src);
        return 1;
    }

    char buf[1024];
    ssize_t n;

    while ((n = read(src, buf, sizeof(buf))) > 0)
    {
        if (write(dest, buf, n) != n)
        {
            break;
        }
    }

    close(src);
    close(dest);
    return 0;
}