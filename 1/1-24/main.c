#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Link.h"
#define MAXLINE 1000
typedef struct
{
    int line;
    int subscript;
    int flag;
}Symbol;//记录符号的位置，类型等信息
#define SYMBOL_SIZE 8
const char left_symbol[8][5] = {"", "\'", "\"", "//", "/*", "(", "[", "{"};//需要匹配的左符号
const char right_symbol[8][5] = {"", "\'", "\"", "\n", "*/", ")", "]", "}"};//需要匹配的右符号

int getLine(char line[], int maxline);//获取一行数据
int strCmp(char str1[], char str2[], int len);//匹配字符串
int checkComment(LinkHead *symbol_match);//检查是否在注释内
int checkQuotate(LinkHead *symbol_match);//检查是否在引号内
int checkMatch(int flag, LinkHead *symbol_match);//检查符号是否匹配
int symbol2flag(char *str, LinkHead *symbol_match);//符号转标志
int main(void)
{
    int len;
    char str[MAXLINE];
    LinkHead *lines_str = creatLink();//存放数据
    LinkHead *symbol_match = creatLink();//存放匹配信息，栈
    while((len = getLine(str, MAXLINE)) > 0)
    {
        if(push_backLink(str, len + 1, lines_str) < 0)
        {
            printf("push_backLink error\n");
            goto FREE;
        }
    }
    int line_count = 0;
    int char_count = 0;
    for(Link *iter = lines_str->head->next; iter != lines_str->tail; iter = iter->next)
    {
        char *str = (char*)iter->data;
        printf("%s", str);
        for(int i = 0; i < strlen(str); i++)
        {
            int flag = symbol2flag(str + i, symbol_match);//获取标志
            int ret = 0;
            if(flag != 0)//如果能获取到标志
            {
                Symbol symbol = {line_count, char_count, flag};
                if(symbol_match->tail->pre->data == NULL)//如果栈内没有数据
                {
                    if(str[i] == '\n')//如果为换行符，则不处理，因为换行符是和'//'匹配的
                        continue;
                    if(flag < 0)//如果为右符号，则表示没有匹配的左符号，报错
                    {
                        putchar('\n');
                        printf("error %d line %d character\n", symbol.line, symbol.subscript);
                        printf("%s\n", right_symbol[-symbol.flag]);
                        goto FREE;
                    }
                    if(push_backLink(&symbol, sizeof(symbol), symbol_match) < 0)//将符号入栈
                    {
                        printf("insufficient memory\n");
                        goto FREE;
                    }
                }
                else if((ret = checkMatch(flag, symbol_match)) != 0)//检查是否有左符号的匹配
                {
                    pop_backLink(symbol_match);//出栈
                }
                else
                {
                    if(str[i] == '\n')
                        continue;
                    if(flag < 0)
                    {
                        putchar('\n');
                        printf("error %d line %d character\n", symbol.line, symbol.subscript);
                        printf("%s\n", right_symbol[-symbol.flag]);
                        goto FREE;
                    }
                    if(push_backLink(&symbol, sizeof(symbol), symbol_match) < 0)
                    {
                        printf("insufficient memory\n");
                        goto FREE;
                    }
                }
            }
            if(str[strlen(str) - 1] == '\n')
            {
                char_count = 0;
                line_count++;
            }
            char_count++;
        }
    }
    if(symbol_match->length != 0)//如果栈内有数据，表示有没匹配的字符
    {
        Symbol *symbol = (Symbol *)symbol_match->tail->pre->data;
        putchar('\n');
        printf("error % d line %d character\n", symbol->line, symbol->subscript);
        printf("%s\n", left_symbol[symbol->flag]);
        goto FREE;
    }
FREE:
    delLink(lines_str);
    delLink(symbol_match);
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
int checkMatch(int flag, LinkHead *symbol_match)
{
    Symbol *data = (Symbol *)symbol_match->tail->pre->data;//获取栈内第顶部的数据
    return (flag + data->flag) == 0;//如果两个值相加为0，则是匹配
}
int checkComment(LinkHead *symbol_match)
{
    Symbol *data = (Symbol *)symbol_match->tail->pre->data;
    if(data->flag == 3 || data->flag == 4)//如果在注释内，则返回1
        return 1;
    return 0;
}
int checkQuotate(LinkHead *symbol_match)
{
    Symbol *data = (Symbol *)symbol_match->tail->pre->data;
    if(data->flag == 1 || data->flag == 2)//如果在引号内则返回1
        return 1;
    return 0;
}
int symbol2flag(char *str, LinkHead *symbol_match)
{
    Symbol *symbol = (Symbol *)symbol_match->tail->pre->data;
    if(symbol != NULL && checkQuotate(symbol_match) != 0)//在引号内
    {
        if(strCmp(str, right_symbol[1], strlen(right_symbol[1])) && (*(str - 1) != '\\' || *(str - 2) == '\\'))//看该引号是否被转义，如果被转义则表示不是被匹配的字符
            return -1;
        else if(strCmp(str, right_symbol[2], strlen(right_symbol[2])) && (*(str - 1) != '\\' || *(str - 2) == '\\'))
            return -2;
        else
            return 0;
    }
    if(symbol != NULL && checkComment(symbol_match) != 0)
    {
        if(strCmp(str, right_symbol[3], strlen(right_symbol[3])))//匹配注释
           return -3;
        if(strCmp(str, right_symbol[4], strlen(right_symbol[4])))
           return -4;
        else
            return 0;
    }
    int flag = 0;
    for(int j = 1; j < SYMBOL_SIZE; j++)//循环查看是否有可以转换为标志
    {
        if(strCmp(str, left_symbol[j], strlen(left_symbol[j])))
        {
            flag = j;
            break;
        }
        if(strCmp(str, right_symbol[j], strlen(right_symbol[j])))
        {
            flag = -j;
            break;
        }
    }
    return flag;
}
