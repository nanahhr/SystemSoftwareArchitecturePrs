#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode)
{
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main()
{
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat file_stat;

    if (dir == NULL)
    {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.')
            continue;

        if (stat(entry->d_name, &file_stat) == 0)
        {
            print_permissions(file_stat.st_mode);
            printf(" %2ld", (long)file_stat.st_nlink);

            struct passwd *pw = getpwuid(file_stat.st_uid);
            struct group *gr = getgrgid(file_stat.st_gid);
            printf(" %s %s", pw ? pw->pw_name : "???", gr ? gr->gr_name : "???");

            printf(" %8lld", (long long)file_stat.st_size);

            char time_buf[80];
            struct tm *tm_info = localtime(&file_stat.st_mtime);
            strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", tm_info);
            printf(" %s %s\n", time_buf, entry->d_name);
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}