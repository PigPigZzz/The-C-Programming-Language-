#include <stdio.h>
#include <string.h>
#include <libnet.h>

#define MAXLINE 1000
#define TAB '\t'
#define BLACK_SPACE ' '
#define TAB_DEFAULT_SIZE 4
int getLine(char line[], int maxline);
int computeBlackSpaceNum(int pos, int tab_size);
int space2tab(char s[], int len, int tab_size);
int printTab(int pos, int tab_size);
int main(int argc, char *argv[])
{
    int len;
    char line[MAXLINE];
    int tab_size = TAB_DEFAULT_SIZE;
    if(argc == 2)
        tab_size = atoi(argv[1]);
    else if(argc > 2)
        return -1;
    while((len = getLine(line, MAXLINE)) > 0)
    {
        if(len <= 0)
            break;
        len = space2tab(line, len, tab_size);
        for(int i = 0, pos = 0; i < len; i++)
        {
            if(line[i] == '\t')
            {
                pos += printTab(pos, tab_size);
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
int space2tab(char s[], int len, int tab_size)
{
    for(int i = 0, pos = 0, space_count = 0; i < len; i++)
    {
        if(s[i] == BLACK_SPACE)
        {
            space_count++;
        }
        else
        {
            pos += space_count + 1;
            space_count = 0;
        }
        int black_num = computeBlackSpaceNum(pos, tab_size);
        if(space_count == black_num)
        {
            i = i - black_num + 1;
            len = len - black_num + 1;
            s[i] = TAB;
            strcpy(s + i + 1, s + i + black_num);
            space_count = 0;
            pos += black_num;
        }
    }
    return len;
}
int printTab(int pos, int tab_size)
{
    int black_spcae = computeBlackSpaceNum(pos, tab_size);
    for(int i = 0; i < black_spcae; i++)
        putchar(BLACK_SPACE);
    return black_spcae;
}
