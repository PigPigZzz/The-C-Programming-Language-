#include <stdio.h>
#include "memory.h"
//#include <stdlib.h>
int main(void)
{
    int *p = (int *)malloc(100 * sizeof(int));
    for(int i = 0; i < 100; i++)
        printf("%d", p[i]);
    free(p);
    putchar('\n');
    p = (int *)calloc(1000, sizeof(int));
    for(int i = 0; i < 1000; i++)
        printf("%d", p[i]);
    putchar('\n');
    return 0;
}

