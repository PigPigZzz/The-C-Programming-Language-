#include <stdio.h>
#include "memory.h"
//#include <stdlib.h>
int main(void)
{
    int *p = (int *)malloc(100 * sizeof(int));

    p = (int *)malloc(0);
    printf("%p\n", p);
    putchar('\n');
    p = (int *)calloc(100000, sizeof(int));
    for(int i = 0; i < 100000; i++)
        printf("%d", p[i]);
    putchar('\n');
    p = (int *)calloc(100000, sizeof(int));
    p = (int *)calloc(100000, sizeof(int));
    p = (int *)calloc(100000, sizeof(int));
    int a[100];
    free(p);
    return 0;
}
