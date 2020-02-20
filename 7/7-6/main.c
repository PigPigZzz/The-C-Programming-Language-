#include <stdio.h>
#include <string.h>

#define LINE_SIZE 1024

int main(int argc, char *argv[])
{
    if(argc != 3)
        return -1;
    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");
    char line1[LINE_SIZE], line2[LINE_SIZE];
    char *fp1, *fp2;
    while((fp1 = fgets(line1, LINE_SIZE, file1)) != NULL && (fp2 = fgets(line2, LINE_SIZE, file2)) != NULL)
    {
        if(strcmp(fp1, fp2) != 0)
        {
            printf("file1:%s\n", fp1);
            printf("file2:%s\n", fp2);
            break;
        }
    }
    if(fp1 == NULL && fp2 != NULL)
    {
        printf("file1:EOF\n");
        printf("file2:%s\n", fp2);
    }
    else if(fp1 != NULL && fp2 == NULL)
    {
        printf("file1:%s\n", fp1);
        printf("file2:EOF\n");
    }
    return 0;
}