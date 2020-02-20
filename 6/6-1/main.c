#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define STRING_STEP_LEN 1024
#define WORD 1
#define COMMENT 2
#define CONSTANT 3
#define PREPROCESSOR 4
#define CHARACTER 5

struct String
{
    char *str;
    int len;
    int size;
};

struct String creatString()
{
    struct String s;
    s.len = 0;
    s.size = STRING_STEP_LEN;
    s.str = realloc(NULL, sizeof(char) * STRING_STEP_LEN);
    return s;
}

void deleteString(struct String *s)
{
    free(s->str);
    s->len = 0;
    s->size = 0;
}

void clearString(struct String *s)
{
    *s->str = '\0';
    s->len = 0;
}

void extendString(struct String *s)
{
    s->size += STRING_STEP_LEN;
    s->str = realloc(s->str, s->size);
}

void pushString(struct String *s, char c)
{
    if(s->size == s->len)
        extendString(s);
    s->str[s->len++] = c;
}

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

int main(void)
{
    struct String s = creatString();
    while(getword(&s) != EOF)
    {
        printf("%s", s.str);
        clearString(&s);
        putchar('\n');
    }
    deleteString(&s);
    return 0;
}