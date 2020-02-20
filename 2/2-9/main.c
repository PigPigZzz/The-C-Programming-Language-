#include <stdio.h>

int bitcount(unsigned x)
{
    int count = 0;
    while(x)
    {
        x &= x - 1;
        count++;
    }
    return count;
}
int main(void)
{
    printf("%d\n", bitcount(234));
    return 0;
}
