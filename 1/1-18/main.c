#include <stdio.h>
#define MAXLINE 1000
int getline(char line[], int maxline);
int main(void)
{
    int len;
    char line[MAXLINE];
    while ((len = getline(line, MAXLINE)) > 0)
        printf("length:%d\tstring:%s", len, line);
    return 0;
}
int getline(char s[],int lim)
{
    int c, i;
    for(i=0; i < lim-1 && (c=getchar())!= EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    if(i == 0)
        return i;
    i--;
    for(; i >= 0; i--)
    {
        if(s[i] == '\n')
            continue;
        else if(s[i] == '\t' || s[i] == ' ')
            s[i] = s[i + 1];
        else
            break;
    }
    i += 2;
    s[i] = '\0';
    return i;
}
