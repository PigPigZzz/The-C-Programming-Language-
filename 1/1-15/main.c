#include <stdio.h>
float convertCelsius(float fahr);
int main(void)
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;
    upper = 300; step = 20;
    printf("Fahrenheit to Centigrade\n");
    fahr = lower;
    while (fahr <= upper)
    {
        celsius = convertCelsius(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}
float convertCelsius(float fahr)
{
    return (5.0/9.0) * (fahr-32.0);
}
