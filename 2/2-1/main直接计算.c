#include <stdio.h>

long computeSignedMax(int bit_size);
long computeSignedMin(int bit_size);
unsigned long computeUnsignedMax(int bit_size);
int main(void)
{
    printf("%ld\n", computeSignedMin(32));
    printf("signed char:\t\t%ld -- %ld\n", computeSignedMin(sizeof(char) * 8), computeSignedMax(sizeof(char) * 8));
    printf("unsigned char:\t\t%lu -- %lu\n", 0l, computeUnsignedMax(sizeof(char) * 8));
    printf("signed short:\t\t%ld -- %ld\n", computeSignedMin(sizeof(short) * 8), computeSignedMax(sizeof(short) * 8));
    printf("unsigned short:\t\t%lu -- %lu\n", 0l, computeUnsignedMax(sizeof(short) * 8));
    printf("signed int:\t\t%ld -- %ld\n", computeSignedMin(sizeof(int) * 8), computeSignedMax(sizeof(int) * 8));
    printf("unsigned int:\t\t%lu -- %lu\n", 0l, computeUnsignedMax(sizeof(int) * 8));
    printf("signed long:\t\t%ld -- %ld\n", computeSignedMin(sizeof(long) * 8), computeSignedMax(sizeof(long) * 8));
    printf("unsigned long:\t\t%lu -- %lu\n", 0l, computeUnsignedMax(sizeof(long) * 8));
    return 0;
}
long computeSignedMax(int bit_size)
{
    long res = 0;
    long exponent = 1;
    for(int i = 0; i < bit_size - 1; i++)
    {
        res += exponent;
        exponent *= 2;
    }
    return res;
}
long computeSignedMin(int bit_size)
{
    return -(computeSignedMax(bit_size) + 1);
}
unsigned long computeUnsignedMax(int bit_size)
{
    unsigned long res = 0;
    unsigned long exponent = 1;
    for(int i = 0; i < bit_size; i++)
    {
        res += exponent;
        exponent *= 2;
    }
    return res;
}
