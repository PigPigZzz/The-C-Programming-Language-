#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Tree.h"

#define LINE_SIZE 1024
#define WORD 1
#define CHARACTOR 2
#define NUMBER 3
#define NEWLINE 4

char *noise_list[] ={"a","an","and","be","but","by","he","I","is","it","off","on","she","so","the","they","you"};

int getword(char *s)
{
    int c, s_count = 0;
    while (isspace(c = getchar()))
        if(c == '\n')
            return NEWLINE;
    if(c == EOF)
        return EOF;
    else if(isalpha(c))
    {
        do
        {
            *s++ = (char)c;
            s_count++;
        }while (isalpha(c = getchar()) || c == '-' || c == '\'');
        *s = '\0';
        ungetc(c, stdin);
        if(s_count == 1)
            return CHARACTOR;
        return WORD;
    }
    else if(isdigit(c))
    {
        do
        {
            *s++ = (char)c;
            s_count++;
        }while (isalnum(c = getchar()) || c == '\'');
        *s = '\0';
        ungetc(c, stdin);
        return NUMBER;
    }
    else
    {
        *s++ = (char)c;
        *s = '\0';
        return CHARACTOR;
    }
}

int main(void)
{
    int type, line_count = 1;
    char s[LINE_SIZE];
    struct Tree root = creatTree();
    OUT:
    while((type = getword(s)) != EOF)
    {
        switch (type)
        {
            case NEWLINE:
                line_count++;
                break;
            case WORD:
                for(int i = 0; i < sizeof(noise_list) / sizeof(char *); i++)
                    if(strcmp(s, noise_list[i]) == 0)
                        goto OUT;
                pushTree(&root, s, line_count);
                break;
        }
    }
    printTree(&root);
    deleteTree(&root);
    return 0;
}