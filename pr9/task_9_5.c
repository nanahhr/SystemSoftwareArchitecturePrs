#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void test_access(const char *filename)
{
    printf("Checking access for '%s':\n", filename);

    if (access(filename, R_OK) == 0)
        printf(" - Read:  ALLOWED\n");
    else
        printf(" - Read:  DENIED\n");

    if (access(filename, W_OK) == 0)
        printf(" - Write: ALLOWED\n");
    else
        printf(" - Write: DENIED\n");
}

int main()
{
    const char *temp_file = "perm_test.tmp";
    char cmd[256];

    int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (fd == -1)
    {
        perror("Failed to create file");
        return 1;
    }
    write(fd, "Initial data\n", 13);
    close(fd);
    printf("File created as regular user.\n");
    test_access(temp_file);

    printf("\nChanging owner to ROOT (requires sudo)...\n");
    sprintf(cmd, "sudo chown root:root %s", temp_file);
    system(cmd);

    printf("Setting permissions to 600 (Root only)...\n");
    sprintf(cmd, "sudo chmod 600 %s", temp_file);
    system(cmd);
    test_access(temp_file);

    printf("\nSetting permissions to 644 (Public read)...\n");
    sprintf(cmd, "sudo chmod 644 %s", temp_file);
    system(cmd);
    test_access(temp_file);

    sprintf(cmd, "sudo rm %s", temp_file);
    system(cmd);

    return 0;
}