#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL)
        {
            perror("Error opening file");
            continue;
        }

        char line[1024];
        int line_count = 0;

        while (fgets(line, sizeof(line), file))
        {
            printf("%s", line);
            line_count++;

            if (line_count >= 20)
            {
                printf("\n--- Press Enter to see more ---");
                getchar();
                line_count = 0;
            }
        }
        fclose(file);
    }
    return 0;
}