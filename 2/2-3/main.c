#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STR_LINE 128
int htoi(char s[]);
int main(void)
{
    char line[STR_LINE];
    gets(line);
    int num = htoi(line);
    printf("%0x\n", num);
    return 0;
}
int htoi(char s[])
{
    int size = strlen(s);
    if(size < 2)
        return 0;
    int num = 0;
    char l_s[STR_LINE];
    strcpy(l_s, s);
    strlwr(l_s);
    if(l_s[0] != '0' && l_s[1] != 'x')
        return 0;
    for(int i = 2; i < size; i++)
    {
        num *= 16;
        if(isdigit(l_s[i]))
        {
            num += l_s[i] - '0';
        }
        else if(isalpha(l_s[i]))
        {
            num += l_s[i] - 'a' + 10;
        }
    }
    return num;
}
