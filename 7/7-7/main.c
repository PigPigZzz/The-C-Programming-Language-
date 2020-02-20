#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

struct
{
    unsigned int excpt : 1;
    unsigned int number : 1;
    unsigned int file : 1;
} flag;

int main(int argc, char *argv[])
{
    char line[MAXLINE], *pattern;
    int c, lineno;
    int file_start;
    if(argc < 2)
        return -1;
    for(int i = 1; i < argc - 1 && *argv[i] == '-'; i++)
    {
        char *p = argv[i];
        while((c = *++p) != '\0')
        {
            switch (c)
            {
                case 'x':
                    flag.excpt = 1;
                    break;
                case 'n':
                    flag.number = 1;
                    break;
                case 'f':
                    flag.file = 1;
                    file_start = i + 1;
                    break;
            }
        }
    }
    pattern = argv[argc - 1];
    if(flag.file)
    {
        while(file_start < argc - 1)
        {
            printf("%s\n", argv[file_start]);
            FILE *fp = fopen(argv[file_start++], "r");
            lineno = 0;
            while(fgets(line, MAXLINE, fp) != NULL)
            {
                lineno++;
                if ((strstr(line, pattern) != NULL) != flag.excpt)
                {
                    if (flag.number)
                        printf("%d:", lineno);
                    printf("%s", line);
                }
            }
        }
    }
    else
    {
        char filename[FILENAME_MAX];
        while(scanf("%s", filename) != EOF)
        {
            FILE *fp = fopen(filename, "r");
            lineno = 0;
            while(fgets(line, MAXLINE, fp) != NULL)
            {
                lineno++;
                if ((strstr(line, pattern) != NULL) != flag.excpt)
                {
                    if (flag.number)
                        printf("%d:", lineno);
                    printf("%s", line);
                }
            }
        }
    }
    return 0;
}