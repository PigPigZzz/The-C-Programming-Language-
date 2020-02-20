//逆波兰表示法
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* next free stack position栈顶指针 */
double val[MAXVAL]; /* value stack值栈 */
int getop(char[]);
void push(double);
double pop(void);
double getValue(void);
void swap(void);
void clear(void);
void duplicate(void);
/* reverse Polish calculator */
int main(void)
{
    int type;
    double op1, op2, top_v;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {//getop获取下个操作数或者运算符
        switch (type) {
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
            case '?':
                top_v = getValue();
                printf("%lf\n", top_v);
                break;
            case '#':
                duplicate();
                break;
            case '~':
                swap();
                break;
            case '!':
                clear();
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
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

double getValue(void)
{
    return val[sp - 1];
}

void swap(void)
{
    double temp = val[sp - 2];
    val[sp - 2] = val[sp - 1];
    val[sp - 1] = temp;
}

void clear(void)
{
    sp = 0;
}

void duplicate(void)
{
    double temp = getValue();
    push(temp);
}

/* getop: get next character or numeric operand */
int getop(char s[])
{
    static int pre_char;
    static int pre_char_flag = 0;
    int i, c;
    while ((s[0] = c = (pre_char_flag != 0 ? pre_char_flag = 0, pre_char : getchar())) == ' ' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* not a number */
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getchar()));
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getchar()));
    s[i] = '\0';
    if(c != EOF)
    {
        pre_char_flag = 1;
        pre_char = c;
    }
    return NUMBER;
}
