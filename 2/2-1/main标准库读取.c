#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    printf("signed char:\t\t%d -- %d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char:\t\t%u -- %u\n", 0, UCHAR_MAX);
    printf("signed short:\t\t%hd -- %hd\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short:\t\t%hu -- %hu\n", 0, USHRT_MAX);
    printf("signed int:\t\t%d -- %d\n", INT_MIN, INT_MAX);
    printf("unsigned int:\t\t%u -- %u\n", 0, UINT_MAX);
    printf("signed long:\t\t%ld -- %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long:\t\t%lu -- %lu\n", 0, ULONG_MAX);
    return 0;
}
