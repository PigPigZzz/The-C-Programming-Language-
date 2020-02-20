#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Tree.h"

#define LINE_SIZE 1024
#define WORD 1
#define CHARACTOR 2
#define NUMBER 3
#define NEWLINE 4
#define WORD_SIZE 1024

struct Word
{
    char *str;
    int count;
};
struct Word word_list[WORD_SIZE];
int word_index = 0;

int word_strcmp(char *a, struct Word *b)
{
    return strcmp(a, b->str);
}

int word_numcmp(struct Word *a, struct Word *b)
{
    return a->count - b->count;
}

struct Word *word_node(char *str, struct Word *element)
{
    if(element == NULL)
    {
        element = word_list + word_index++;
        memset(element, 0, sizeof(struct Word));
        element->str = strdup(str);
    }
    element->count++;
    return element;
}

void word_print(struct Word *element)
{
    printf("%s : %d\n", element->str, element->count);
}

void word_free(struct Word *element)
{
    free(element->str);
}

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
    int type;
    char s[LINE_SIZE];
    struct Tree root = creatTree();
    while((type = getword(s)) != EOF)
    {
        if(type == WORD)
        {
            pushTree(&root, s, word_strcmp, word_node);
        }
    }
    qsort(word_list, word_index, sizeof(struct Word), word_numcmp);
    for(int i = 0; i < word_index; i++)
        printf("%s : %d\n", word_list[i].str, word_list[i].count);
    //printTree(&root, word_print);
    printf("%d\n", word_index);
    deleteTree(&root, word_free);
    return 0;
}