#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main()
{
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat file_stat;

    if (dir == NULL)
    {
        perror("opendir failed");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        char *ext = strrchr(entry->d_name, '.');
        if (ext != NULL && strcmp(ext, ".c") == 0)
        {

            printf("\nFound file: %s\n", entry->d_name);
            printf("Grant 'read' permission for other users? (y/n): ");

            char choice;
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y')
            {
                if (stat(entry->d_name, &file_stat) == 0)
                {
                    if (chmod(entry->d_name, file_stat.st_mode | S_IROTH) == 0)
                    {
                        printf("Success: Permissions updated for %s\n", entry->d_name);
                    }
                    else
                    {
                        perror("chmod failed");
                    }
                }
            }
            else
            {
                printf("Skipped.\n");
            }
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}