#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define DECIMAL 1
#define OCTAL 2
#define HEXADECIMAL 3

struct Number
{
    int flag;
    union
    {
        int i_value;
        float f_value;
    } value;
};

int check_flag(char *s)
{
    if(strcmp(s, "-o") == 0)
        return OCTAL;
    else if(strcmp(s, "-h") == 0)
        return HEXADECIMAL;
    else
        return DECIMAL;
}

int check_number(struct Number *numbers, int size, char *s, int flag)
{
    int count = 0;
    for(int i = 0; s[i] != '\0'; i++)
    {
        int j = i;
        if(isdigit(s[j]))
        {
            int num = 0;
            int num_power = 0;
            while (isdigit(s[j]))
            {
                num *= 10;
                num += s[j] - '0';
                j++;
            }
            if (s[j] == '.' && isdigit(s[j + 1]))
            {
                j++;
                while (isdigit(s[j]))
                {
                    num *= 10;
                    num += s[j] - '0';
                    j++;
                    num_power++;
                }
            }
            strcpy(s + i + 2, s + j);
            if (num_power != 0)
            {
                numbers->value.f_value = (float) num / pow(10, num_power);
                numbers->flag = 1;
                strncpy(s + i, "%f", 2);
            }
            else
            {
                numbers->value.i_value = num;
                numbers->flag = 2;
                if(flag == DECIMAL)
                    strncpy(s + i, "%d", 2);
                else if(flag == OCTAL)
                    strncpy(s + i, "%o", 2);
                else if(flag == HEXADECIMAL)
                    strncpy(s + i, "%x", 2);
            }
            i = j - 1;
            numbers++;
            count++;
        }
    }
    numbers->flag = 0;
    return count;
}

void myprintf(char *s, struct Number *numbers, void *(*callback)(struct Number *))
{
    while(*s != '\0')
    {
        if(*s == '%')
        {
            s++;
            switch (*s)
            {
                case 'd':
                    printf("%d", *(int*)callback(numbers));
                    break;
                case 'o':
                    printf("%o", *(int*)callback(numbers));
                    break;
                case 'x':
                    printf("%x", *(int*)callback(numbers));
                    break;
                case 'f':
                    printf("%f", *(float*)callback(numbers));
                    break;
            }
        }
        else
            putchar(*s);
        s++;
    }
}

void *next_value(struct Number *numbers)
{
    static int i  = 0;
    static struct Number value;
    value = numbers[i++];
    if(numbers[i].flag == 0)
        i = 0;
    if(value.flag == 1)
        return &value.value.f_value;
    else
        return &value.value.i_value;
}

int main(int argc, char *argv[])
{
    struct Number numbers[100];
    int flag =  DECIMAL;
    if(argc == 1)
        return 0;
    flag = check_flag(argv[1]);
    for(int i = 2; i < argc; i++)
    {
        check_number(numbers, 100, argv[i], flag);
        myprintf(argv[i], numbers, next_value);
        putchar('\n');
    }
}