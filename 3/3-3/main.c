#include <stdio.h>
#include <string.h>

void expand(char s1[], char s2[])
{
    static const char upper_alph[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char lower_alph[27] = "abcdefghijklmnopqrstuvwxyz";
    static const char digits[11] = "0123456789";

    int len = strlen(s1) + 1;
    char *start, *end;
    int i, j;
    for(i = 1, j = 0; i < len; i++)
    {
        s2[j++] = s1[i - 1];
        if(s1[i] == '-')
        {
            if(((start = strchr(upper_alph, s1[i - 1])) != NULL) && ((end = strchr(upper_alph, s1[i + 1])) != NULL) ||
               ((start = strchr(lower_alph, s1[i - 1])) != NULL) && ((end = strchr(lower_alph, s1[i + 1])) != NULL) ||
               ((start = strchr(digits, s1[i - 1])) != NULL) && ((end = strchr(digits, s1[i + 1])) != NULL))
            {
                if(*start != '\0' && *end != '\0')
                {
                    if(start < end)
                    {
                        start++;
                        while(start < end)
                        {
                            s2[j++] = *start++;
                        }
                        i++;
                    }
                }
            }
        }
    }
    s2[j] = '\0';
}

int main(void)
{
    /*"a-z-", "z-a-", "-1-6-",
      "a-ee-a", "a-R-L", "1-9-1",
      "5-5"};*/
    char s1[] = "5-5";
    char s2[1024];
    expand(s1, s2);
    printf("%s\n", s2);
    return 0;
}

