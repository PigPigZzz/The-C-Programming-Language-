#include <stdio.h>
#include <string.h>

void swap(char *a, char *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void reverse(char *s, int left, int right)
{
    if(left >= right)
        return;
    reverse(s, left + 1, right - 1);
    swap(&s[left], &s[right]);
}

int main(void)
{
    char s[] = "dufsdiuofews";
    reverse(s, 0, strlen(s) - 1);
    printf("%s\n", s);
}
