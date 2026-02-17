#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <aio.h>
#include <errno.h>
#include <omp.h>

#include "module1.h"
#include "module2.h"

int main()
{
    long val1 = 5;
    int val2 = 12;

    long start_val1 = val1;
    int start_val2 = val2;

    static char buffer[256];
    struct aiocb cb;

    printf("=== SYSTEM START (OpenMP + AIO) ===\n");

#pragma omp parallel sections
    {
#pragma omp section
        {
            printf("[Thread %d] Calculating Module 1...\n", omp_get_thread_num());
            module1_computation(&val1);
        }

#pragma omp section
        {
            printf("[Thread %d] Calculating Module 2...\n", omp_get_thread_num());
            module2_computation(&val2);
        }
    }

    snprintf(buffer, sizeof(buffer),
             "--- EXECUTION REPORT ---\n"
             "Module 1 (Sum): input %ld -> result %ld\n"
             "Module 2 (Fact): input %d -> result %d\n",
             start_val1, val1, start_val2, val2);

    int fd = open("execution_results.log", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Failed to open file");
        return 1;
    }

    memset(&cb, 0, sizeof(struct aiocb));
    cb.aio_fildes = fd;
    cb.aio_buf = buffer;
    cb.aio_nbytes = strlen(buffer);

    printf("Main: Sending report to disk asynchronously...\n");
    if (aio_write(&cb) == -1)
    {
        perror("aio_write failed");
        close(fd);
        return 1;
    }

    while (aio_error(&cb) == EINPROGRESS)
    {
        printf("Main: Disk is busy writing...\n");
        usleep(5000);
    }

    if (aio_error(&cb) == 0)
    {
        printf("Main: Write completed. %zd bytes saved to log.\n", aio_return(&cb));
    }
    close(fd);
    printf("Program finished.\n");

    return 0;
}