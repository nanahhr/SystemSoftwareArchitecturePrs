#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigsegv(int sig)
{
    printf("\nStack limit exceeded (SIGSEGV/Stack Overflow)\n");
    exit(1);
}

void recursive_function(int depth)
{
    char buffer[1024 * 64]; // 64 КБ

    buffer[0] = (char)(depth % 256);

    if (depth % 5 == 0)
    {
        printf("Current depth: %d (Stack used approx: %d KB)\n", depth, depth * 64);
    }

    recursive_function(depth + 1);
}

int main()
{
    signal(SIGSEGV, handle_sigsegv);
    printf("Starting recursion with small stack limit...\n");
    recursive_function(1);
    return 0;
}