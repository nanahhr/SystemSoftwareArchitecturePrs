#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "module1.h"
#include "module2.h"

int main()
{
    pthread_t thread1, thread2;

    long val1 = 5;
    int val2 = 12;

    printf("Main: Creating threads...\n");

    if (pthread_create(&thread1, NULL, module1_computation, (void *)&val1))
    {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    if (pthread_create(&thread2, NULL, module2_computation, (void *)&val2))
    {
        fprintf(stderr, "Error creating thread 2\n");
        return 2;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main: All threads finished. Exiting.\n");

    return 0;
}