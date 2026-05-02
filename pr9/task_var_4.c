#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void test_fs_behavior(const char *path)
{
    printf("\nTesting: %s \n", path);

    if (creat(path, 0000) == -1)
    {
        printf("Creation failed: %s\n", strerror(errno));
        return;
    }

    struct stat st;
    if (stat(path, &st) == 0)
    {
        printf("File created with mode: %o\n", st.st_mode & 0777);
    }

    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        printf("Read attempt (normal user): FAILED (%s)\n", strerror(errno));
    }
    else
    {
        printf("Read attempt (normal user): SUCCESS (Unexpected!)\n");
        fclose(f);
    }

    char cmd[256];
    sprintf(cmd, "sudo cat %s > /dev/null 2>&1", path);
    if (system(cmd) == 0)
    {
        printf("Read attempt (root): SUCCESS\n");
    }
    else
    {
        printf("Read attempt (root): FAILED\n");
    }

    unlink(path);
}

int main()
{
    test_fs_behavior("./test_ext4.tmp");

    test_fs_behavior("/dev/shm/test_tmpfs.tmp");

    printf("\n[Note] NFS test skipped: requires active network mount.\n");

    return 0;
}