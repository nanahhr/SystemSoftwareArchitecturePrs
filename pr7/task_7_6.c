#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int main()
{
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat st;
    char *dirs[1024];
    int count = 0;

    if (!dir)
        return 1;

    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] == '.')
            continue;

        if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode))
        {
            dirs[count] = strdup(entry->d_name);
            count++;
        }
    }
    closedir(dir);

    qsort(dirs, count, sizeof(char *), compare);

    printf("Sorted subdirectories:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s/\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}