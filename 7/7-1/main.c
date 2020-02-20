#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LOWER "lower"
#define UPPER "upper"

#define CHECK(s1, s2) strcmp(s1, s2 + strlen(s2) - strlen(s1))

int main(int argc, char *argv[])
{
    int flag, c, letter_case;
    size_t argv_len = strlen(*argv);
    if(CHECK(LOWER, *argv) == 0)
        flag = 0;
    else if(CHECK(UPPER, *argv) == 0)
        flag = 1;
    else
    {
        puts("argv[0] error");
        return -1;
    }
    while((c = getchar()) != EOF)
    {
        if(flag == 0)
            letter_case = tolower(c);
        else if(flag == 1)
            letter_case = toupper(c);
        putchar(letter_case);
    }
    return 0;
}