#include <stdio.h>
#include <stdarg.h>
#include <string.h>

char symbol_set[] = "dioxXucsfeEgGp%";

int getConversionChar(char *s, char **out_conversion)
{
    static char conversion_ch[10];
    char *p = conversion_ch;
    *p++ = *s++;
    while(*s != '\0')
    {
        *p++ = *s;
        for(int i = 0; i < sizeof(symbol_set) / sizeof(char) - 1; i++)
            if(*s == symbol_set[i])
            {
                *p = '\0';
                *out_conversion = conversion_ch;
                return *s;
            }
        s++;
    }
    return -1;
}

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *conversion_ch;
    int type;
    va_start(ap, fmt);
    for(char *p = fmt; *p != '\0'; p++)
    {
        if(*p == '%')
        {
            type = getConversionChar(p, &conversion_ch);
            switch(type)
            {
                case 'd':case 'i':case 'o':
                case 'x':case 'X':case 'u':
                case 'c':
                    printf(conversion_ch, va_arg(ap, int));
                    break;
                case 's':
                    printf(conversion_ch, va_arg(ap, char*));
                    break;
                case 'f':case 'e':case 'E':
                case 'g':case 'G':
                    printf(conversion_ch, va_arg(ap, double));
                    break;
                case 'p':
                    printf(conversion_ch, va_arg(ap, void*));
                    break;
                default:
                    printf(conversion_ch);
                    break;
            }
            p += strlen(conversion_ch) - 1;
        }
        else
            putchar(*p);
    }
    va_end(ap);
}

int main(void)
{
    minprintf("char:%c,int:%d,long:%ld,longlong:%lld,float:%f,double:%lf,string:%s\n", 'a', 1, 2, 3, 3.14, 100.212, "hello world");
    return 0;
}