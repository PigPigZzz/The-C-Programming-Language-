#include <stdio.h>
#include <stdlib.h>
char *itoa(int n, char *s)
{
    static int flag = 0;
    if(flag == 0)
    {
        flag = n < 0 ? -1 : 1;
    }
    if(n == 0)
    {
        if(flag == -1)
        {
            *s = '-';
            flag = 0;
            return s + 1;
        }
        flag = 0;
        return s;
    }
    s = itoa(n / 10, s);
    *s = abs(n % 10) + '0';
    return s + 1;
}

int main(void)
{
    char s[100] = "";
    itoa(433252312, s);
    printf("%s\n", s);
    itoa(-433252312, s);
    printf("%s\n", s);
}
