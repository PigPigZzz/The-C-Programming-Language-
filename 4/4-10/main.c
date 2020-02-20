//逆波兰表示法
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER 1 /* signal that a number was found */
#define MATHFUN 2
#define VARIABLE 3
#define MAXVAL 100 /* maximum depth of val stack */
#define ALPHA_NUM 26
#define BUFFSIZE 100
#define OP_SIZE 100

struct Stack
{
    union
    {
        double number;
        char variable;
    };
    int flag;
};

int sp = 0; /* next free stack position栈顶指针 */
struct Stack val[MAXVAL]; /* value stack值栈 */
double variable_num[ALPHA_NUM];
int getop(char[]);
void push(struct Stack);
struct Stack pop(void);
struct Stack getValue(void);
void swap(void);
void clear(void);
void duplicate(void);
void mathFun(char s[]);
char **getLine(void);
/* reverse Polish calculator */
int main(void)
{
    int type;
    struct Stack op1, op2, top_v;
    double op1_num, op2_num, top_v_num;
    char s[MAXOP];
    struct Stack tmp_val;
    double recent_val = 0;
    while ((type = getop(s)) != EOF) {//getop获取下个操作数或者运算符
        switch (type) {
            case NUMBER:
                tmp_val.flag = NUMBER;
                tmp_val.number = atof(s);//将字符串转为浮点数
                push(tmp_val);
                break;
            case MATHFUN:
                mathFun(s);
                break;
            case VARIABLE:
                tmp_val.flag = VARIABLE;
                tmp_val.variable = s[0];
                push(tmp_val);
                break;
            case '+':
                op1 = pop();
                op2 = pop();
                op1_num = op1.flag == NUMBER ? op1.number : variable_num[op1.variable - '0'];
                op2_num = op2.flag == NUMBER ? op2.number : variable_num[op2.variable - '0'];
                tmp_val.flag = NUMBER;
                tmp_val.number = op1_num + op2_num;
                push(tmp_val);
                break;
            case '*':
                op1 = pop();
                op2 = pop();
                op1_num = op1.flag == NUMBER ? op1.number : variable_num[op1.variable - '0'];
                op2_num = op2.flag == NUMBER ? op2.number : variable_num[op2.variable - '0'];
                tmp_val.flag = NUMBER;
                tmp_val.number = op1_num * op2_num;
                push(tmp_val);
                break;
            case '-':
                op1 = pop();
                op2 = pop();
                op1_num = op1.flag == NUMBER ? op1.number : variable_num[op1.variable - '0'];
                op2_num = op2.flag == NUMBER ? op2.number : variable_num[op2.variable - '0'];
                tmp_val.flag = NUMBER;
                tmp_val.number = op2_num - op1_num;
                push(tmp_val);
                break;
            case '/':
                op1 = pop();
                op2 = pop();
                op1_num = op1.flag == NUMBER ? op1.number : variable_num[op1.variable - '0'];
                op2_num = op2.flag == NUMBER ? op2.number : variable_num[op2.variable - '0'];
                if (op1_num != 0.0)
                {
                    tmp_val.flag = NUMBER;
                    tmp_val.number = op2_num / op1_num;
                    push(tmp_val);
                }
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op1 = pop();
                op2 = pop();
                op1_num = op1.flag == NUMBER ? op1.number : variable_num[op1.variable - '0'];
                op2_num = op2.flag == NUMBER ? op2.number : variable_num[op2.variable - '0'];
                if (op1_num != 0.0)
                {
                    tmp_val.flag = NUMBER;
                    tmp_val.number = (int)op2_num % (int)op1_num;
                    push(tmp_val);
                }
                else
                    printf("error: zero divisor\n");
                break;
            case '=':
                op1 = pop();
                op2 = pop();
                if(op2.flag == VARIABLE)
                {
                    op1_num = op1.flag == NUMBER ? op1.number : variable_num[op1.variable - '0'];
                    variable_num[op2.variable - '0'] = op1_num;
                    push(op1);
                }
                else
                {
                    printf("error: \'=\' can assignment a variable only\n");
                    clear();
                }
                break;
            case '?':
                top_v = getValue();
                top_v_num = top_v.flag == NUMBER ? top_v.number : variable_num[top_v.variable - '0'];
                printf("%lf\n", top_v_num);
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
            case '$':
                getop(s);
                printf("the recent value is %.8g\n", recent_val);
                break;
            case '\n':
                top_v = pop();
                top_v_num = top_v.flag == NUMBER ? top_v.number : variable_num[top_v.variable - '0'];
                recent_val = top_v_num;
                printf("\t%.8g\n", top_v_num);
                clear();
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
/* push: push f onto value stack */
void push(struct Stack f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push\n");
}
/* pop: pop and return top value from stack */
struct Stack pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        struct Stack tmp = {0.0, NUMBER};
        printf("error: stack empty\n");
        return tmp;
    }
}

struct Stack getValue(void)
{
    return val[sp - 1];
}

void swap(void)
{
    struct Stack temp = val[sp - 2];
    val[sp - 2] = val[sp - 1];
    val[sp - 1] = temp;
}

void clear(void)
{
    sp = 0;
}

void duplicate(void)
{
    struct Stack temp = getValue();
    push(temp);
}

void mathFun(char s[])
{
    struct Stack tmp;
    struct Stack op1, op2;
    double op1_num, op2_num;
    double tmp_num;
    if(strcmp(s, "sin") == 0)
    {
        tmp = pop();
        tmp_num = tmp.flag == NUMBER ? tmp.number : variable_num[tmp.variable - '0'];
        tmp.number = sin(tmp_num);
        tmp.flag = NUMBER;
        push(tmp);
    }
    else if(strcmp(s, "cos") == 0)
    {
        tmp = pop();
        tmp_num = tmp.flag == NUMBER ? tmp.number : variable_num[tmp.variable - '0'];
        tmp.number = cos(tmp_num);
        tmp.flag = NUMBER;
        push(tmp);
    }
    else if(strcmp(s, "exp") == 0)
    {
        tmp = pop();
        tmp_num = tmp.flag == NUMBER ? tmp.number : variable_num[tmp.variable - '0'];
        tmp.number = exp(tmp_num);
        tmp.flag = NUMBER;
        push(tmp);
    }
    else if(strcmp(s, "pow") == 0)
    {
        op1 = pop();
        op2 = pop();
        op1_num = op1.flag == NUMBER ? op1.number : variable_num[op1.variable - '0'];
        op2_num = op2.flag == NUMBER ? op2.number : variable_num[op2.variable - '0'];
        tmp.flag = NUMBER;
        tmp.number = pow(op2_num, op1_num);
        push(tmp);
    }
    else
        printf("%s is not a support function", s);
}

/* getop: get next character or numeric operand */
int getop(char s[])
{
    static char **ops = NULL;
    if(ops == NULL || *ops == NULL)
        ops = getLine();
    char *str = *ops;
    ops++;
    int i = 0;
    if(isalpha(str[i]))
    {
        while(isalpha(s[i] = str[i])) i++;
        if(i == 1)
            return VARIABLE;
        else
            return MATHFUN;
    }
    if (!isdigit(str[i]) && str[i] != '.')
        return str[i]; /* not a number */
    if (isdigit(str[i])) /* collect integer part */
        while (isdigit(s[i] = str[i])) i++;
    if (str[i] == '.') /* collect fraction part */
    {
        s[i] = str[i];
        i++;
        while (isdigit(s[i] = str[i])) i++;
    }
    return NUMBER;
}

char **getLine(void)
{
    static char str[BUFFSIZE];
    static char *ops[OP_SIZE];
    memset(str, 0, BUFFSIZE);
    memset(ops, 0, sizeof(char*) * OP_SIZE);
    fgets(str, BUFFSIZE, stdin);
    int ops_i = 0, str_i = 0;
    while(str[str_i] != '\0')
    {
        if(str[str_i] == ' ' || str[str_i] == '\t')
        {
            str[str_i] = '\0';
            if(ops[ops_i] != NULL)
                ops_i++;
        }
        else if(str[str_i] == '\n')
        {
            str[str_i++] = '\0';
            str[str_i] = '\n';
            ops_i++;
            ops[ops_i] = str + str_i;
        }
        else if(ops[ops_i] == NULL)
            ops[ops_i] = str + str_i;
        str_i++;
    }
    return ops;
}