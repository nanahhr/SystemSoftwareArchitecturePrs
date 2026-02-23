#include <stdio.h>
#include <stdlib.h>

int global_init = 100;
int global_uninit;
void expand_stack(int depth)
{
    int large_array[1000];

    printf("Stack level %d (large array address): %p\n", depth, (void *)&large_array);
    if (depth < 2)
    {
        expand_stack(depth + 1);
    }
}
int main()
{
    int stack_var;
    int *heap_var = malloc(16);

    if (heap_var == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Text (code) segment: %p\n", (void *)main);
    printf("Data segment:        %p\n", (void *)&global_init);
    printf("BSS segment:         %p\n", (void *)&global_uninit);
    printf("Heap:                %p\n", (void *)heap_var);
    printf("Stack top:           %p\n", (void *)&stack_var);

    expand_stack(1);
    free(heap_var);
    return 0;
}