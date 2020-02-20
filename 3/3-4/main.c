#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

void itoa(long long num, char s[])
{
    int i = 0;
    if(num < 0)
        s[i++] = '-';
    do
    {
        s[i++] = abs(num % 10) + '0';
        num /= 10;
    }while(num);
    s[i] = '\0';
    if(s[0] == '-')
      strrev(s + 1);
    else
      strrev(s);
}

int main(void)
{
    long long num = LLONG_MIN;
    char s[1024];
    itoa(num, s);
    printf("%lld\n", num);
    puts(s);
}
