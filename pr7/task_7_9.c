#include <stdio.h>
#include <sys/time.h>
#include <math.h>

int main()
{
    struct timeval start, end;

    gettimeofday(&start, NULL);

    double result = 0;
    for (int i = 0; i < 10000000; i++)
    {
        result += sqrt(i);
    }

    gettimeofday(&end, NULL);

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = (seconds * 1000.0) + (microseconds / 1000.0);

    printf("Result: %f\n", result);
    printf("Execution time: %.3f ms\n", elapsed);

    return 0;
}