#include <stdio.h>
#define MAXLINE 1000
int getline(char line[], int maxline);
void reverse(char s[], int length);
int main(void)
{
    int len;
    char line[MAXLINE];
    while ((len = getline(line, MAXLINE)) > 0)
    {
        reverse(line, len);
        printf("length:%d\tstring:%s", len, line);
    }
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
    s[i] = '\0';
    return i;
}
void reverse(char s[], int length)
{
    int i = 0, j;
    for(j = length; s[j] == '\n' || s[j] == '\0'; j--);
    while(i < j)
    {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
}
