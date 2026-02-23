#include <stdio.h>
#include <time.h>
#include <limits.h>

int main()
{
    printf("Architecture: %zu-bit\n", sizeof(void *) * 8);
    printf("Size of time_t: %zu bytes\n\n", sizeof(time_t));

    time_t max_32bit = 2147483647;
    printf("32-bit time_t limit: %s", ctime(&max_32bit));

    time_t future_64bit = max_32bit * 2;
    printf("Beyond 32-bit limit: %s", ctime(&future_64bit));

    return 0;
}