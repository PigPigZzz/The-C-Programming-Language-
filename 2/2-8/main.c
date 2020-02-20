#include <stdio.h>
unsigned rightrot(unsigned x, int n)
{
    return (x >> n) | (x << (sizeof(x) * 8 - n));
}
int main(void)
{
    printf("%u\n", rightrot(3, 32));
    return 0;
}
