#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "String.h"
#include "Tree.h"

#define WORD 1
#define COMMENT 2
#define CONSTANT 3
#define PREPROCESSOR 4
#define CHARACTER 5

int getword(struct String *s)
{
    int c, escape_flag = 0;
    while(isspace(c = getchar()));
    if(c == EOF)
        return EOF;
    else if(c == '#')//处理预处理
    {
        pushString(s, (char)c);
        while((isalnum(c = getchar()) || (c == '\n' && escape_flag)) && c != EOF)//预处理结尾为/都可换行到下一行
        {
            if(c == '\\')
                escape_flag = 1;
            else
                escape_flag = 0;
            pushString(s, (char)c);
        }
        ungetc(c, stdin);
        pushString(s, '\0');
        return PREPROCESSOR;
    }
    else if(c == '\'')//处理单引号
    {
        pushString(s, (char)c);
        while(((c = getchar()) != '\'' || escape_flag) && c != EOF)
        {
            if(c == '\\')
                escape_flag = !escape_flag;
            else
                escape_flag = 0;
            pushString(s, (char)c);
        }
        if(c != EOF)
            pushString(s, (char)c);
        else
            ungetc(c, stdin);
        pushString(s, '\0');
        return CONSTANT;
    }
    else if(c == '\"')//处理双引号
    {
        pushString(s, (char)c);
        while(((c = getchar()) != '\"' || escape_flag) && c != EOF)
        {
            if(c == '\\')
                escape_flag = !escape_flag;
            else
                escape_flag = 0;
            pushString(s, (char)c);
        }
        if(c != EOF)
            pushString(s, (char)c);
        else
            ungetc(c, stdin);
        pushString(s, '\0');
        return CONSTANT;
    }
    else if(c == '/')
    {
        pushString(s, (char)c);
        switch (c = getchar())
        {
            case '/':
                pushString(s, (char)c);
                while(((c = getchar()) != '\n' || escape_flag) && c != EOF)
                {
                    if(c == '\\')
                        escape_flag = 1;
                    else
                        escape_flag = 0;
                    pushString(s, (char)c);
                }
                if(c != EOF)
                    pushString(s, (char)c);
                else
                    ungetc(c, stdin);
                pushString(s, '\0');
                return COMMENT;
            case '*':
                pushString(s, (char)c);
                int asterisk = 0;
                while(((c = getchar()) != '/' || asterisk) && c != EOF)
                {
                    asterisk = 0;
                    if(c == '*')
                        asterisk = 1;
                    pushString(s, (char)c);
                }
                if(c != EOF)
                    pushString(s, (char)c);
                else
                    ungetc(c, stdin);
                pushString(s, '\0');
                return COMMENT;
            default:
                ungetc(c, stdin);
                pushString(s, '\0');
                return CHARACTER;
        }
    }
    else if(isalpha(c))
    {
        pushString(s, (char)c);
        while(isalnum(c = getchar()) || c == '_')
            pushString(s, (char)c);
        ungetc(c, stdin);
        pushString(s, '\0');
        return WORD;
    }
    else
    {
        pushString(s, (char)c);
        pushString(s, '\0');
        return CHARACTER;
    }
}

int main(int argc, char *argv[])
{
    struct String s = creatString();
    struct Tree root = creatTree();
    int n = 6;
    int type;
    if(argc == 2)
        n = atoi(argv[1]);
    while((type = getword(&s)) != EOF)
    {
        if(type == WORD && s.len >= n)
        {
            pushTree(&root, s.str, n);
        }
        clearString(&s);
    }
    printTree(&root);
    deleteString(&s);
    deleteTree(&root);
    return 0;
}
