#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Running as UID: %u\n", getuid());
    printf("Attempting to read /etc/shadow using sudo...\n\n");

    int status = system("sudo cat /etc/shadow | head -n 3");

    if (status == 0)
    {
        printf("\n[SUCCESS] Command executed with administrative privileges.\n");
    }
    else
    {
        printf("\n[ERROR] Could not execute command. Check sudo permissions.\n");
    }

    return 0;
}