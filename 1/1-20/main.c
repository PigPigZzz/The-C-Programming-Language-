#include <stdio.h>
#define MAXLINE 1000
#define TAB '\t'
#define BLACK_SPACE ' '
int getLine(char line[], int maxline);
int computeBlackSpaceNum(int pos, int tab_size);
int main(void)
{
    int len;
    char line[MAXLINE];
    int tab_size = 5;
    while((len = getLine(line, MAXLINE)) > 0)
    {
        if(len <= 0)
            break;
        for(int i = 0, pos = 0; i < len; i++)
        {
            if(line[i] == TAB)
            {
                int black_space_num = computeBlackSpaceNum(pos, tab_size);
                for(int j = 0; j < black_space_num; j++)
                    putchar(BLACK_SPACE);
                pos += black_space_num;
            }
            else
            {
                putchar(line[i]);
                pos++;
            }
        }
    }
    return 0;
}
int getLine(char s[],int lim)
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
int computeBlackSpaceNum(int pos, int tab_size)
{
    return tab_size - (pos % tab_size);
}
