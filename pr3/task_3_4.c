#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

void draw_lottery(int count, int range)
{
    printf("Drawing %d from %d: ", count, range);
    for (int i = 0; i < count; i++)
    {
        printf("%d ", (rand() % range) + 1);
    }
    printf("\n");
}

void handle_sigxcpu(int sig)
{
    printf("\nCPU time limit exceeded (SIGXCPU)\n");
    exit(1);
}

int main()
{
    signal(SIGXCPU, handle_sigxcpu);
    srand(time(NULL));

    printf("Starting endless lottery simulation to test CPU limit...\n");

    while (1)
    {
        draw_lottery(7, 49);
        draw_lottery(6, 36);

        double dummy = 0;
        for (int j = 0; j < 100000; j++)
        {
            dummy += j * 0.01;
        }
    }

    return 0;
}