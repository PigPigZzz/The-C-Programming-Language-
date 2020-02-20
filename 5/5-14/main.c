#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_N_SIZE 64
#define STR_SIZE 1024
#define LEXICOGRAPHY 1
#define NUMERICALLY 2
#define REVERSE 4

int getLine(char **s);
int readLine(char ***output);
void myqsort(void **array, int left, int right, int (*cmp)(void *, void *));

int r_strcmp(char *a, char *b);
int numcmp(char *a, char *b);
int r_numcmp(char *a, char *b);

int main(int argc, char *argv[])
{
    char **lines;
    unsigned int flag = LEXICOGRAPHY;
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            if(strcmp(argv[i], "-n") == 0)
            {
                flag &= ~LEXICOGRAPHY;
                flag |= NUMERICALLY;
            }
            else if(strcmp(argv[i], "-r") == 0)
                flag |= REVERSE;
        }
    }
    int line_size = readLine(&lines);
    for(int i = 0; i < line_size; i++)
        printf("%s", lines[i]);
    switch (flag)
    {
        case LEXICOGRAPHY:
            myqsort(lines, 0, line_size, strcmp);
            break;
        case NUMERICALLY:
            myqsort(lines, 0, line_size, numcmp);
            break;
        case LEXICOGRAPHY | REVERSE:
            myqsort(lines, 0, line_size, r_strcmp);
            break;
        case NUMERICALLY | REVERSE:
            myqsort(lines, 0, line_size, r_numcmp);
            break;
    }
    putchar('\n');
    for(int i = 0; i < line_size; i++)
        printf("%s", lines[i]);
    return 0;
}

int getLine(char **s)
{
    static char str[STR_SIZE + 1];
    int size;
    int line_size = 0;
    do
    {
        if(fgets(str, STR_SIZE + 1, stdin) == NULL)
            return EOF;
        size = strlen(str);
        *s = realloc(*s, (line_size + size) * sizeof(char));
        memset(*s + line_size, '\0', size);
        line_size += size;
        strcat(*s, str);
    } while(size == STR_SIZE && str[STR_SIZE - 1] != '\n');
    return line_size;
}

int readLine(char ***output)
{
    int line_n_size = LINE_N_SIZE;
    int line_n = 0;
    char **line_p = realloc(NULL, STR_SIZE * sizeof(char *));
    memset(line_p + line_n, 0, LINE_N_SIZE * sizeof(char *));
    while(getLine(line_p + line_n) != EOF)
    {
        line_n++;
        if(line_n == line_n_size)
        {
            line_p = realloc(line_p, (line_n_size + LINE_N_SIZE) * sizeof(char *));
            line_n_size += LINE_N_SIZE;
            memset(line_p + line_n, NULL, LINE_N_SIZE * sizeof(char *));
        }
    }
    *output = line_p;
    return line_n;
}

void myqsort(void **array, int left, int right, int (*cmp)(void *, void *))
{
    void swap(void **v, int i, int j);
    int last = left;
    if(left >= right)
        return;
    swap(array, left, (left + right) / 2);
    for(int i = left + 1; i < right; i++)
        if((*cmp)(array[i], array[left]) < 0)
            swap(array, i, ++last);
    swap(array, last, left);
    myqsort(array, left, last, cmp);
    myqsort(array, last + 1, right, cmp);
}

void swap(void **v, int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int r_strcmp(char *a, char *b)
{
    return strcmp(b, a);
}

int numcmp(char *a, char *b)
{
    double v1, v2;
    v1 = atof(a);
    v2 = atof(b);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int r_numcmp(char *a, char *b)
{
    return numcmp(b, a);
}