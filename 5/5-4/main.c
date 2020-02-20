#include <stdio.h>
#include <string.h>

int strend(char *s, char *t)
{
    s += strlen(s) - strlen(t);
    while(*s != '\0')
    {
        if(*s++ != *t++)
            return 0;
    }
    return 1;
}

int main(void)
{
    char s[20] = "hello world";
    char *t = "world";
    int res = strend(s, t);
    printf("%d\n", res);
    return 0;
}