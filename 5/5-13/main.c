#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_N_SIZE 64
#define STR_SIZE 1024
#define LAST_N 10

int getLine(char **s);

int main(int argc, char *argv[])
{
    int line_n_size = LINE_N_SIZE;
    int line_n = 0;
    char **line_p = realloc(NULL, STR_SIZE * sizeof(char *));
    memset(line_p + line_n, 0, LINE_N_SIZE * sizeof(char *));
    int last_n = LAST_N;
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            if(*argv[i] == '-')
            {
                int tmp = atoi(argv[i] + 1);
                if(tmp != 0)
                {
                    last_n = tmp;
                    break;
                }
            }
        }
    }
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
    for(int i = line_n < last_n ? 0 : line_n - last_n; i < line_n; i++)
        printf("%s", line_p[i]);
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