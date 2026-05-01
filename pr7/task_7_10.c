#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    float n;
    srand(time(NULL));

    printf("Enter the upper limit (n): ");
    if (scanf("%f", &n) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    float rand_0_1 = (float)rand() / (float)RAND_MAX;

    float rand_0_n = ((float)rand() / (float)RAND_MAX) * n;

    printf("\n--- Random Numbers ---\n");
    printf("(a) Range [0.0; 1.0]: %f\n", rand_0_1);
    printf("(b) Range [0.0; %.2f]: %f\n", n, rand_0_n);

    return 0;
}