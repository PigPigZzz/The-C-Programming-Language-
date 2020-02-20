#include <stdio.h>
#include <limits.h>

int isupper1(int c)
{
    return 'A' <= c && c <= 'Z';
}

char table[UCHAR_MAX] = {0};
int isupper2(int c)
{
    return table[c];
}

int main(void)
{
    for(int i = 'A'; i <= 'Z'; i++)
        table[i] = 1;
    int a = 'D', b = 'F';
    if(isupper1(a))
        printf("%c is upper\n", a);
    if(isupper2(b))
        printf("%c is upper\n", b);
}