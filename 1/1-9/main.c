#include <stdio.h>
int main(void)
{
    int c;
    int is_black = 0;
    while((c = getchar()) != EOF)
    {
        if(c == ' ')
            is_black = 1;
        else
        {
            if(is_black == 1)
                putchar(' ');
            is_black = 0;
            putchar(c);
        }
    }
    return 0;
}
