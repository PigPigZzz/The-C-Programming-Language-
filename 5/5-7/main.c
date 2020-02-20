#include <stdio.h>

#define MAXLINES 5000
#define MAXLEN 1000

int getLine(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = (char)c;
    if (c == '\n')
    {
        s[i++] = (char)c;
    }
    s[i] = '\0';
    return i;
}

int readlines(char lines[][MAXLEN], int maxlines)
{
    int len, nlines;

    nlines = 0;
    while ((len = getLine(lines[nlines], MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else
            lines[nlines++][len - 1] = '\0';  /* delete the newline */
    return nlines;
}

void writelines(char lineptr[][MAXLEN], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int main(void)
{
    char lineptr[MAXLINES][MAXLEN];
    int nlines = readlines(lineptr, MAXLINES);
    writelines(lineptr, nlines);
}