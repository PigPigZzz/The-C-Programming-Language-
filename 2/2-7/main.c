#include <stdio.h>
unsigned invert(unsigned x, int p, int n)
{
    return ((~x) & ((~0 << (p + 1)) ^ (~0 << (p - n + 1)))) | (x & ~((~0 << (p + 1)) ^ (~0 << (p - n + 1))));
}
int main(void)
{
    printf("%d\n", invert(1, 13, 8));
    return 0;
}
