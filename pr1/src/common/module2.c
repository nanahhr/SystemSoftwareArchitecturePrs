#include <stdio.h>
#include "module2.h"

void *module2_computation(void *arg)
{
    int n = *(int *)arg;
    unsigned long long fact = 1;

    for (int i = 1; i <= n; i++)
    {
        fact *= i;
    }

    *(int *)arg = (int)fact;
    printf("Module 2: Finished. Result saved: %llu\n", fact);
    return NULL;
}