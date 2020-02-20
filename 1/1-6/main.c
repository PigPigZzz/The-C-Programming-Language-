#include <stdio.h>
int main(void)
{
    int c;
    while(c = getchar() != EOF)
        putchar(c + '0');
    putchar(c + '0');
    return 0;
}
