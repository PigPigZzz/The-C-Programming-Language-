//逆波兰表示法
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100

int getch(void);
void ungetch(int);
int buf[BUFSIZE]; /* buffer for ungetch */
int bufs = 0; /* next free position in buf */
int bufe = 0;
int sp = 0; /* next free stack position栈顶指针 */
double val[MAXVAL]; /* value stack值栈 */
int getop(char[]);
void push(double);
double pop(void);
/* reverse Polish calculator */
int main(int argc, char *argv[])
{
    int type;
    double op1, op2;
    char s[MAXOP];
    if(argc == 1)
        return 0;
    else
    {
        for(int i = 1; i < argc; i++)
        {
            for(int j = 0; argv[i][j] != '\0'; j++)
                ungetch(argv[i][j]);
            ungetch(' ');
        }
        ungetch('\n');
    }
    while ((type = getop(s)) != EOF)//getop获取下个操作数或者运算符
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s));//将字符串转为浮点数
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                op1 = pop();
                if (op2 != 0.0)
                    push((int)op1 % (int)op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}
/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* not a number */
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()));
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

int getch(void) /* get a (possibly pushed-back) character */
{
    int ch =  (bufs != bufe) ? buf[bufs] : EOF;//如果有之前超前读取的字符在缓冲数组中则先返回缓冲数组中的字符
    bufs = (bufs + 1) % BUFSIZE;
    return ch;
}
void ungetch(int c) /* push character back on input */
{
    if (((bufe + 1) % BUFSIZE) == bufs)
        printf("ungetch: too many characters\n");
    else
    {
        buf[bufe] = c;
        bufe = (bufe + 1) % BUFSIZE;
    }
}
