#include <stdio.h>
#include <string.h>
#define MAXLINE 1000
#define MAXWORDS 100
#define COLUMNSIZE 11
#define IN 1
#define OUT 0
int getLine(char line[], int maxline);
int getWords(char line[], int subscript_start_end[][2],  char word_split_char[][COLUMNSIZE]);
void subStr(char dest[], char src[], int sub_size);
int main(void)
{
    int len;
    char line[MAXLINE];
    char short_str[COLUMNSIZE];
    int word_subscript[MAXWORDS][2];
    char word_split_char[MAXWORD][COLUMNSIZE];
    int line_offset = 0;
    while((len = getLine(line + line_offset, MAXLINE)) > 0)
    {
        line_offset = 0;
        int word_num = getWords(line, word_subscript, word_split_char );
        int index = 0;
        while(index < word_num)
        {
            int offset = 0;
            int word_count = 0;
            while(index < word_num && offset < COLUMNSIZE)
            {
                offset += word_subscript[index][1] - word_subscript[index][0];
                for(int i = 0; word_split_char[index][i] != '\0'; i++)
                {
                    if(word_split_char[index][i] == '\t')
                        offset += 8 - (offset % 8);
                    else if(word_split_char[index][i] == ' ')
                        offset++;
                    else if(word_split_char[index][i] == '\n')
                        offset += COLUMNSIZE;
                }
                word_count++;
                index++;
            }
            if(offset < COLUMNSIZE)
            {
                subStr(line, line + word_subscript[index - word_count][0], word_subscript[index - word_count][0] - word_subscript[index][1]);
                line_offset += word_subscript[index - word_count][0] - word_subscript[index][1];
                word_num = 0;
            }
            else
            {
                for(int i = index - word_count; i < index; i++)
                {
                    subStr(short_str, line + word_subscript[i][0], word_subscript[i][1] - word_subscript[i][0]);
                    printf("%s", short_str);
                    printf("%s", word_split_char[i]);
                }
                putchar('\n');
            }
        }
    }
    return 0;
}
int getLine(char s[],int lim)
{
    int c, i;
    for(i=0; i < lim-1 && (c=getchar())!= EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
int getWords(char line[], int subscript_start_end[][2],  char word_split_char[][COLUMNSIZE])
{
    int state = OUT;
    int char_count = 0;
    int word_count = 0;
    for(int i = 0; line[i] != '\0'; i++)
    {
        if(line[i] == '\n' || line[i] == ' ' || line[i] == '\t')
        {
            if(state == IN)
            {
                state = OUT;
                word_count++;
                (*subscript_start_end)[0] = i - char_count;
                (*subscript_start_end)[1] = i;
                subscript_start_end++;
                int j;
                for(j = i; line[j] == '\n' || line[j] == ' ' || line[j] == '\t'; j++);
                subStr(*word_split_char, line + i, j - i);
                word_split_char++;
                i = j - 1;
                char_count = 0;
            }
        }
        else
        {
            state = IN;
            char_count++;
        }
    }
    return word_count;
}
void subStr(char dest[], char src[], int sub_size)
{
    int i;
    for(i = 0; i < sub_size; i++)
        dest[i] = src[i];
    dest[i] = '\0';
}
