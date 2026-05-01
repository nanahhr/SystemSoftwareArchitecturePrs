#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int main()
{
    DIR *dir = opendir(".");
    struct dirent *entry;
    char choice;

    if (dir == NULL)
    {
        perror("Unable to open directory");
        return EXIT_FAILURE;
    }
    printf("Warning: Deleted files cannot be recovered.\n\n");

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.')
        {
            continue;
        }

        if (strcmp(entry->d_name, "task_7_8.c") == 0 || strcmp(entry->d_name, "task_7_8") == 0)
        {
            continue;
        }

        printf("Delete file '%s'? (y/n): ", entry->d_name);

        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y')
        {
            if (remove(entry->d_name) == 0)
            {
                printf("Successfully deleted: %s\n", entry->d_name);
            }
            else
            {
                perror("Error deleting file");
            }
        }
        else
        {
            printf("File '%s' kept.\n", entry->d_name);
        }
    }

    closedir(dir);
    printf("\nFinished processing directory.\n");

    return EXIT_SUCCESS;
}