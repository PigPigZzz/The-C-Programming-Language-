#include <stdio.h>
int main(void)
{
    float fahr, celsius;
    float lower, upper, step;
    lower = -20;
    upper = 150; step = 7;
    printf("Centigrade to Fahrenheit\n");
    celsius = lower;
    while (celsius <= upper)
    {
        fahr = (9.0 / 5.0) * celsius + 32;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return 0;
}
