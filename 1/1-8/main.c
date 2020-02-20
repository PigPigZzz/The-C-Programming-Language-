#include <stdio.h>
int main(void)
{
    int c;
    int newline_count = 0, black_count = 0, tab_count = 0;
    while((c = getchar()) != EOF)
    {
        if(c == '\n')
            newline_count++;
        else if(c == '\t')
            tab_count++;
        else if(c == ' ')
            black_count++;
    }
    printf("blanks:%d\n", black_count);
    printf("tabs:%d\n", tab_count);
    printf("newlines:%d\n", newline_count);
    return 0;
}
