#include <stdio.h>
#include <string.h>
#define MAXLINE 1000
int getLine(char line[], int maxline);
int strCmp(char str1[], char str2[], int len);
int main(void)
{
    int len;
    char str[MAXLINE];
    char line_note_char[2][3] = {"//", "\n"};//行注释
    char long_note_char[2][3] = {"/*", "*/"};//多行注释
    char quote_char[2][3] = {"\"", "\""};//引号
    char escape_char[2] = "\\";//转义字符
    int quote_flag = 0;//引号标志
    int long_note_flag = 0;//多行注释标志
    int line_note_flag = 0;//行注释标志
    int line_note_subscript = 0;//行注释起始位置
    int long_note_subscript = 0;//多行注释起始位置
    while((len = getLine(str, MAXLINE)) > 0)
    {
        /*
        处理只有一个首字母是'\"'的情况
        */
        if(str[0] == '\"')
            quote_flag = (quote_flag + 1) % 2;

        for(int i = 1; str[i] != '\0'; i++)
        {
            int flag = 0;
            flag = quote_flag | (line_note_flag << 1) | (long_note_flag << 2);//如果有一个标志位为1，则给出对应的操作
            if(flag == 0 || (flag >> 1) & 1)//处理行注释
            {
                if(strCmp(str + i - 1 + line_note_flag, line_note_char[line_note_flag], strlen(line_note_char[line_note_flag])) == 1)
                {
                    if(line_note_flag == 0)
                    {
                        line_note_subscript = i - 1;
                    }
                    else
                    {
                        strcpy(str + line_note_subscript, str + i);
                    }
                    line_note_flag = (line_note_flag + 1) % 2;
                    continue;
                }
            }
            if(flag == 0 || (flag >> 2) & 1)//处理多行注释
            {
                if(strCmp(&str[i - 1], long_note_char[long_note_flag], 2) == 1)
                {
                    if(long_note_flag == 0)
                    {
                        long_note_subscript = i - 1;
                    }
                    else
                    {
                        strcpy(str + long_note_subscript, str + i + 1);
                    }
                    long_note_flag = (long_note_flag + 1) % 2;
                    continue;
                }
            }
            if(flag == 0 || flag & 1)//处理引号
            {
                if(strCmp(str + i, quote_char[quote_flag], strlen(quote_char[quote_flag])) == 1)
                {
                    if(quote_flag == 1 && strCmp(str + i - 1, escape_char, strlen(escape_char)) == 1 && str[i - 2] != '\\')
                        continue;
                    quote_flag = (quote_flag + 1) % 2;
                    continue;
                }
            }
        }
        if(long_note_flag)//多行注释未遇到结尾标志
        {
            str[long_note_subscript] = '\0';
            long_note_subscript = 0;
        }
        else if(line_note_flag)//行注释未遇到‘\n’
        {
            str[line_note_subscript] = '\0';
            line_note_subscript = 0;
        }
        printf("%s", str);
    }
    return 0;
}
int getLine(char s[],int lim)
{
    int c, i;
    for(i=0; i < lim - 1 && (c = getchar())!= EOF && c != '\n'; ++i)
        s[i] = c;
    if(c == '\n')
    {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}
int strCmp(char str1[], char str2[], int len)
{
    for(int i = 0; i < len; i++)
        if(str1[i] != str2[i])
            return 0;
    return 1;
}
