#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    const char *user_file = "user_source.txt";
    const char *root_file = "root_copy.txt";

    system("echo 'Original content' > user_source.txt");
    printf(" Created file '%s' as regular user.\n", user_file);

    char cmd[256];
    sprintf(cmd, "sudo cp %s %s", user_file, root_file);
    system(cmd);
    printf("Copied to '%s' as root (UID 0).\n", root_file);

    printf("Attempting to modify '%s' as current user...\n", root_file);
    int mod_status = system("echo 'Modified content' >> root_copy.txt 2> /dev/null");
    if (mod_status != 0)
    {
        printf("   Result: Modification FAILED (Permission denied).\n");
    }

    printf("Attempting to delete '%s' using rm...\n", root_file);
    int del_status = system("rm root_copy.txt 2> /dev/null");
    if (del_status == 0)
    {
        printf("   Result: Deletion SUCCESSFUL (Directory permissions allow this).\n");
    }
    else
    {
        printf("   Result: Deletion FAILED.\n");
    }

    unlink(user_file);

    return 0;
}