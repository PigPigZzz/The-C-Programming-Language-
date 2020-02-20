#include <stdio.h>
#define IN 1
#define OUT 0
int main(void)
{
    int c;
    int state = OUT;
    while((c = getchar()) != EOF)
    {
        if(c == '\n' || c == ' ' || c == '\t')
        {
            if(state == IN)
            {
                state = OUT;
                putchar('\n');
            }
        }
        else
        {
            state = IN;
            putchar(c);
        }
    }
    return 0;
}
