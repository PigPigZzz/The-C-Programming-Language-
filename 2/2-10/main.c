#include <stdio.h>
#include <string.h>
#define LINE_MAX 1024
void lower(char *s)
{
    for(int i = 0; i < strlen(s); i++)
    {
        s[i] = isupper(s[i]) ? tolower(s[i]) : s[i];
    }
}
int main(void)
{
    char s[LINE_MAX];
    fgets(s, LINE_MAX, stdin);
    lower(s);
    printf("%s", s);
    return 0;
}
