#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

void itoa(long long num, char s[], int width)
{
    int i = 0;
    int flag = num < 0 ? 1 : 0;
    do
    {
        s[i++] = abs(num % 10) + '0';
        num /= 10;
    }while(num);
    if(flag)
        s[i++] = '-';
    while (i < width )
        s[i++] = ' ';
    s[i] = '\0';
    strrev(s);
}


int main(void)
{
    long long num = 1430;
    char s[1024];
    itoa(num, s, 20);
    printf("%20lld\n", num);
    puts(s);
}
