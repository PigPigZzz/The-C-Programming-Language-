#include <stdio.h>
#include <string.h>

void escape(char s[],char t[])
{
    int len = strlen(t) + 1;
    for(int i = 0, j = 0; i < len; i++, j++)
    {
        switch(t[i])
        {
        case '\n':
            s[j++] = '\\';
            s[j] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j] = 't';
            break;
        case '\a':
            s[j++] = '\\';
            s[j] = 'a';
            break;
        case '\b':
            s[j++] = '\\';
            s[j] = 'b';
            break;
        case '\f':
            s[j++] = '\\';
            s[j] = 'f';
            break;
        case '\r':
            s[j++] = '\\';
            s[j] = 'r';
            break;
        case '\v':
            s[j++] = '\\';
            s[j] = 'v';
            break;
        case '\\':
            s[j++] = '\\';
            s[j] = '\\';
            break;
        case '\"':
            s[j++] = '\\';
            s[j] = '\"';
            break;
        default:
            s[j] = t[i];
            break;
        }
    }
}

void unescape(char s[], char t[])
{
    int len = strlen(t) + 1;
    for(int i = 0, j = 0; i < len; i++, j++)
    {
        switch(t[i])
        {
        case '\\':
            switch(t[++i])
            {
                case 'n':
                s[j] = '\n';
                break;
            case 't':
                s[j] = '\t';
                break;
            case 'a':
                s[j] = '\a';
                break;
            case 'b':
                s[j] = '\b';
                break;
            case 'f':
                s[j] = '\f';
                break;

            case 'r':
                s[j] = '\r';
                break;
            case 'v':
                s[j] = '\v';
                break;
            case '\\':
                s[j] = '\\';
                break;
            case '\"':
                s[j] = '\"';
                break;
            default:
                s[j++] = '\\';
                s[j] = t[i];
                break;
            }
            break;
        default:
            s[j] = t[i];
            break;
        }
    }
}

int main(void)
{
    char text1[50] = "\aHello,\n\tWorld! Mistakee\b was \"Extra 'e'\"!\n";
    char text2[51];
    printf("Original string:\n%s\n", text1);
    escape(text2, text1);
    printf("Escaped string:\n%s\n", text2);
    unescape(text1, text2);
    printf("Unescaped string:\n%s\n", text1);
    return 0;
}

