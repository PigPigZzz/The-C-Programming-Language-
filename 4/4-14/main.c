#include <stdio.h>

#define swap(t, x, y) \
{\
    t tmp = x;\
    x = y;\
    y = tmp;\
}


int main(void)
{
    int a = 132;
    int b = 2534;
    swap(int, a, b);
    printf("a = %d,b = %d\n", a, b);
}
