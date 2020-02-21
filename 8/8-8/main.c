#include <stdio.h>
#include "memory.h"
//#include <stdlib.h>
int main(void)
{
    int a[1024];
    bfree(a, sizeof(a));
    char *p = malloc(sizeof(int) * 100);
    printf("a:%p\n", a + 1024);
    printf("p:%p\n", p + 25 * 16);
    return 0;
}
