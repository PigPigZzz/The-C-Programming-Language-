#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

void itob(int n, char s[], int b)
{
    const static char CharCode[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    int i = 0;
    if(n < 0)
        s[i++] = '-';
    do
    {
        s[i++] = CharCode[abs(n % b)];
        n /= b;
    } while(n);
    s[i] = '\0';
    if(s[0] == '-')
        strrev(s + 1);
    else
        strrev(s);
}

int main(void)
{
    long long num = 1543511;
    char s[1024];
    itob(num, s, 8);
    printf("%o\n", num);
    puts(s);
}
