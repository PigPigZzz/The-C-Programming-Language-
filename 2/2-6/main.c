#include <stdio.h>
unsigned setbits(unsigned x, int p, int n, int y)
{
    return (~((~0 << (p + 1)) ^ (~0 << (p - n + 1))) & x) | ((y << (p - n + 1)) & ((~0 << (p + 1)) ^ (~0 << (p - n + 1))));
}
int main(void)
{
    printf("%d\n", setbits(1, 5, 4, 7));
    return 0;
}
