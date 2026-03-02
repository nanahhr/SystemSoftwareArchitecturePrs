#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int roll_dice()
{
    return (rand() % 6) + 1;
}

void handle_sigxfsz(int sig)
{
    printf("\nThe file size limit has been exceeded.\n");
    exit(1);
}

int main()
{
    signal(SIGXFSZ, handle_sigxfsz);

    FILE *file = fopen("dice_results.txt", "w");
    if (file == NULL)
    {
        perror("Failed to open file for writing");
        return 1;
    }

    srand(time(NULL));
    printf("Simulating dice rolls and writing to a file...\n");

    for (int i = 1; i <= 2000; i++)
    {
        int dice = roll_dice();

        if (fprintf(file, "Roll %d: result: %d\n", i, dice) < 0)
        {
            printf("Error writing at iteration %d\n", i);
            break;
        }

        fflush(file);
    }

    fclose(file);
    printf("Writing completed successfully (limit not reached).\n");
    return 0;
}