//
// Created by xjs on 2020/2/7.
//

#include "String.h"
#include <stdlib.h>

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