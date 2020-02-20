#include <stdio.h>
#include <libnet.h>

#define MAXLINE 1000
#define TAB '\t'
#define BLACK_SPACE ' '
#define TAB_DEFAULT_START 0;
#define TAB_DEFAULT_STOP 4;
int getLine(char line[], int maxline);
int computeBlackSpaceNum(int pos, int tab_size);
int main(int argc, char *argv[])
{
    int len;
    char line[MAXLINE];
    int tab_start = TAB_DEFAULT_START;
    int tab_stop = TAB_DEFAULT_STOP;
    if(argc > 1 && argc < 4)
    {
        for(int i = 1; i < argc; i++)
        {
            if(*(argv[i]) == '+')
                tab_stop = atoi(argv[i] + 1);
            else if(*(argv[i]) == '-')
                tab_start = atoi(argv[i] + 1);
            else
                return -1;
        }
    }
    else if(argc >= 4)
        return -1;
    int tab_size = tab_start + tab_stop;
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
                while(pos % tab_size < tab_start)
                {
                    putchar(BLACK_SPACE);
                    pos++;
                }
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
