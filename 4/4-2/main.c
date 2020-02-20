#include <stdio.h>
#include <ctype.h>
#include <math.h>

double atof(char s[])
{
    double val = 0, power = 1, exp = 0;
    int val_sign = 1, exp_sign = 1;
    while(*s == ' ') s++;
    if(*s == '+' || *s == '-')
        val_sign = *s++ == '+' ? 1 : -1;
    while(isdigit(*s))
    {
        val *= 10;
        val += *s - '0';
        s++;
    }
    if(*s == '.')
        s++;
    while(isdigit(*s))
    {
        val *= 10;
        val += *s - '0';
        power *= 10;
        s++;
    }
    if(tolower(*s) == 'e')
        s++;
    if(*s == '-' || *s == '+')
        exp_sign = *s++ == '+' ? 1 : -1;
    while(isdigit(*s))
    {
        exp *= 10;
        exp += *s - '0';
        s++;
    }
    exp *= -exp_sign;
    power = power * pow(10, exp);
    return val_sign * val / power;
}

int main(void)
{
    double num = atof("   123.3e-12");
    printf("%.20lf\n", num);
    return 0;
}
