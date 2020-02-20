#include <stdio.h>

void strncpy(char *s, char *t, int n)
{
    while(n-- && (*s++ = *t++));
}

void strncat(char *s, char *t, int n)
{
    while(*s++);
    s--;
    while(n-- && (*s++ = *t++));
}

int strncmp(char *s, char *t, int n)
{
    while(n-- && (*s++ == *t++))
        if(*s == '\0')
            return 0;
    if(n == 0)
        return 0;
    else
        return *--s - *--t;
}

int main(void)
{
    char s[20] = "hello s";
    char *t = "world";
    strncat(s, t, 5);
    printf("%s\n", s);
    int res = strncmp(s + 6, t, 4);
    printf("%d\n", res);
    return 0;
}