#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int maxline);
int main(void)
{
    int len;
    char str[MAXLINE];
    while((len = getLine(str, MAXLINE)) > 0)
    {
        printf("%s", str);
    }
    return 0;
}
int getLine(char s[],int lim)
{
    int c, i;
    for(i=0; i < lim - 1; ++i)
    {
        if((c = getchar())!= EOF)
            if(c != '\n')
            {
                s[i] = c;
                continue;
            }
        break;
    }
    if(c == '\n')
    {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}
