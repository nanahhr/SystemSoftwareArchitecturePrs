#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    FILE *fp;
    char line[256];
    uid_t my_uid = getuid();
    int found_others = 0;

    fp = popen("getent passwd", "r");
    if (fp == NULL)
    {
        perror("Failed to run getent");
        return EXIT_FAILURE;
    }

    printf("Your UID: %u\n\n", my_uid);
    printf("Other regular users found:\n");

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char *token;
        char *username, *uid_str;
        char line_copy[256];

        strcpy(line_copy, line);

        username = strtok(line_copy, ":");
        strtok(NULL, ":");
        uid_str = strtok(NULL, ":");

        if (uid_str != NULL)
        {
            int uid = atoi(uid_str);

            if (uid >= 1000 && uid != (int)my_uid)
            {
                printf("- User: %s (UID: %d)\n", username, uid);
                found_others = 1;
            }
        }
    }

    if (!found_others)
    {
        printf("No other regular users detected.\n");
    }

    pclose(fp);
    return EXIT_SUCCESS;
}