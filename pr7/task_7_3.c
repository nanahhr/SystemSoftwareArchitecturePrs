#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    char line[1024];
    char *pattern = argv[1];

    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, pattern) != NULL)
        {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}