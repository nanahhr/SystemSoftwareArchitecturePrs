#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void list_files_recursive(const char *path)
{
    struct dirent *entry;
    struct stat statbuf;
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        char full_path[1024];

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &statbuf) == 0)
        {
            if (S_ISDIR(statbuf.st_mode))
            {
                printf("[DIR]  %s\n", full_path);
                list_files_recursive(full_path);
            }
            else
            {
                printf("[FILE] %s\n", full_path);
            }
        }
    }
    closedir(dir);
}

int main()
{
    printf("Starting recursive list from current directory:\n");
    list_files_recursive(".");
    return 0;
}