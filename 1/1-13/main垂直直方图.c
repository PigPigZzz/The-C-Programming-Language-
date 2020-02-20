//垂直直方图：
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define IN 1//正在输入单词
#define OUT 0//没有单词输入
#define WORD_STEP 10//每次二维数组扩充的步长
#define STR_LENGTH 50//最大单词存放长度
#define SPACING 26//单词之间的距离，距离为该(数值*2)
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
    int *hist_num = NULL;
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

    hist_num = (int*)malloc(sizeof(int) * words_index);
    for(int i = 0; i < words_index; i++)//计算各个单词所占百分比
    {
        hist_num[i] = round((float)strlen(words[i]) / (float)all_word_length * 100);//计算该单词长度占总单词长度的百分比
    }
    for(int i = 100; i > 0; i--)//从垂直直方图顶端开始画
    {
        for(int j = 0; j < words_index; j++)
        {
            if(i == hist_num[j] + 1)//如果当前数值是该所占百分比加一，则打印该数值
            {
                int black_num = SPACING - 11;//计算需要打印的空格数
                for(int k = 0; k < black_num / 2; k++)
                    putchar(' ');
                printf("%4d%%/%-5d", hist_num[j], (int)strlen(words[j]));
                for(int k = 0; k < black_num / 2 + black_num % 2; k++)
                    putchar(' ');
            }
            else if(i == hist_num[j])
            {
                int black_num = SPACING - 1;
                for(int k = 0; k < black_num / 2; k++)
                    putchar(' ');
                putchar('*');
                for(int k = 0; k < black_num / 2 + black_num % 2; k++)
                    putchar(' ');
            }
            else if(i < hist_num[j])
            {
                int black_num = SPACING - 1;
                for(int k = 0; k < black_num / 2; k++)
                    putchar(' ');
                putchar('#');
                for(int k = 0; k < black_num / 2 + black_num % 2; k++)
                    putchar(' ');
            }
            else
                for(int k = 0; k < SPACING; k++)
                    putchar(' ');
        }
        putchar('\n');
    }
    for(int i = 0; i < words_index; i++)//打印每个单词
    {
        int word_length = strlen(words[i]);
        int black_num = SPACING - word_length;
        for(int i = 0; i < black_num / 2; i++)
            putchar(' ');
        printf("%s", words[i]);
        for(int i = 0; i < black_num / 2 + black_num % 2; i++)
            putchar(' ');
    }

FREE:
    for(int i = 0; i < words_index; i++)//释放二维数组中每个一维数组
    {
        free(words[i]);
    }
    free(words);
    free(hist_num);
    return 0;
}
