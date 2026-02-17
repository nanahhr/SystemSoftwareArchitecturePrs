#include <stdio.h>
#include "module1.h"

void *module1_computation(void *arg)
{
    long input = *(long *)arg;
    long sum = 0;

    for (long i = 0; i < 1000000000; i++)
    {
        sum += input;
    }
    *(long *)arg = sum;
    printf("Module 1: Finished. Result saved: %ld\n", sum);
    return NULL;
}