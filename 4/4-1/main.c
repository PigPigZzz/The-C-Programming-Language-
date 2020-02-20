#include <stdio.h>
#include <string.h>

int strindex(char s[], char t[])
{
    int t_len = strlen(t);
    for(int i = strlen(s) - t_len; i >= 0; i--)
    {
        if(strncmp(s + i, t, t_len) == 0)
            return i;
    }
    return -1;
}

int main(void)
{
    char s[] = "hello world";
    char t[] = "lo";
    int index = strindex(s, t);
    printf("%d\n", index);
    return 0;
}
