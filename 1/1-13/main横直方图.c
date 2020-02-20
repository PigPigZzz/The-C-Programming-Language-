//横直方图：
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define IN 1//正在输入单词
#define OUT 0//没有单词输入
#define WORD_STEP 10//每次二维数组扩充的步长
#define STR_LENGTH 50//最大单词存放长度
int main(void)
{
    char **words = (char **)malloc(sizeof(char*) * WORD_STEP);//创建二维数组存放单词
    int words_length = WORD_STEP;//当前二维数组可存放的单词数量长度
    int words_index = 0;//当前已使用的二维数组的数量
    char str[STR_LENGTH + 1];//存放单词
    int str_index = 0;//当前已存放的字母数量
    int c;//获取输入流字符
    int state = OUT;//当前在为输入是否为单词的状态
    int all_word_length = 0;//总共单词数量
    while((c = getchar()) != EOF)
    {
        if(c == '\n' || c == ' ' || c == '\t')
        {
            if(state == IN)//当前状态为输入单词状态则进行处理
            {
                all_word_length += str_index;//增加总单词长度
                str[str_index] = '\0';//单词字符串结尾增加'\0'符
                str_index++;
                words[words_index] = (char*)malloc(sizeof(char) * str_index);//创建一个一维数组存放字符串
                if(words[words_index] == NULL)//内存分配失败
                {
                    printf("not enough memory\n");
                    goto FREE;//跳转至释放内存，结束程序
                }
                strcpy(words[words_index], str);
                state = OUT;//修改状态
                str_index = 0;
                words_index++;
                if(words_index == words_length)//如果已经存放的单词数量达到上限，则扩容数组
                {
                    char **words_temp = (char **)realloc(words, (words_length + WORD_STEP) * sizeof(char *));//扩容二维数组
                    if(words_temp == NULL)//内存分配失败
                    {
                        printf("not enough memory\n");
                        goto FREE;//跳转至释放内存，结束程序
                    }
                    words = words_temp;
                    words_length += WORD_STEP;//能存放单词的总数量增加
                }
            }
        }
        else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            if(str_index == STR_LENGTH)//单词长度达到上限
                continue;
            str[str_index] = c;
            str_index++;
            state = IN;
        }
        else//处理未定义的符号
        {
            state = OUT;
            str_index = 0;
        }
    }

    for(int i = 0; i < words_index; i++)//计算并画出直方图
    {
        int word_length = strlen(words[i]);
        int hist_num = round((float)word_length / (float)all_word_length * 100);//计算该单词长度占总单词长度的百分比
        printf("%s:", words[i]);
        for(int j = 0; j < hist_num; j++)
            putchar('=');
        putchar('>');
        printf("%d%%/%d\n", hist_num, word_length);
    }

FREE:
    for(int i = 0; i < words_index; i++)//释放二维数组中每个一维数组
    {
        free(words[i]);
    }
    free(words);
    return 0;
}
