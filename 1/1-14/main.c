#include <stdio.h>
int main(void)
{
    int char_frequence[256] = {0};
    int c;
    while((c = getchar()) != EOF)
    {
        char_frequence[c]++;
    }
    for(int i = 0; i < 256; i++)
    {
        if(char_frequence[i] != 0)
        {
            putchar((char)i);
            for(int j = 0; j < char_frequence[i] - 1; j++)
                putchar('=');
            putchar('>');
            printf("%d\n", char_frequence[i]);
        }
    }
    return 0;
}
