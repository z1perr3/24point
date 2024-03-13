#include "calc.h"
double stack_num[20];  //运算数栈
char stack_op[20];  //运算符栈
int top_num,top_op = -1;  //栈顶位置
int Precede(char a,char b)  //比较运算符a和b的优先级。如果a > b 返回 1；a == b 返回0；a<b 返回-1
{
    switch (a)
    {
        case '+':
            if(b == '*' || b == '/' || b == '(') return -1;
            else return 1;
            break;
        case '-':
           if(b == '*' || b == '/' || b == '(') return -1;
           else return 1;
           break;
        case '*':
           if(b == '(') return -1;
           else return 1;
           break;
        case '/':
           if(b == '(') return -1;
           else return 1;
           break;
        case '(':
           if(b == ')') return 0;
           else return -1;
           break;
        case ')':
            return 1;
            break;
        case '#':
            if(b == '#') return 0;
            else return -1;
            break;
    }
}

double yunsuan(double a,double b,char op)  //两个运算数之间的四则运算
{
    double r;
    if(op == '+') r = a+b;
    if(op == '-') r = a-b;
    if(op == '*') r = a*b;
    if(op == '/') r = a/b;
    return r;
}

double jisuan(char *ch) //计算字符串ch的值
{
    int i = 1;
    int num;
    double num1,num2;
    char op;
    double res;
    stack_op[++top_op] = '#'; //先让'#'进栈
    while(ch[i] != '\0')
    {
        if(ch[i] >= 48 && ch[i] <= 57)  //说明是数字
        {
            num = ch[i] - 48;
            stack_num[++top_num] = num; //进栈
            i++;
        }
        else  //说明就是运算符
        {

            if(Precede(stack_op[top_op],ch[i]) == -1)  //优先级比栈顶元素大
            {
                stack_op[++top_op] = ch[i];
                i++;
                 //printf("栈顶元素为：%.2f\n",stack_num[top_num]);
            }
            else if(Precede(stack_op[top_op],ch[i]) == 0) //优先级相等
            {
                top_op --; //出栈
                i++;
            }  
            else  if(Precede(stack_op[top_op],ch[i]) == 1)
            {
                    
                    num1 = stack_num[top_num--]; //取栈顶元素，出栈
                    num2 = stack_num[top_num--];//取栈顶元素，出栈
                    op = stack_op[top_op--]; //取栈顶元素，出栈
                   // printf("%c\n",op);
                    res = yunsuan(num2,num1,op);
                    //printf("num2 = %.2f,num1 = %.2f,op = %c,res=%.2f\n",num2,num1,op,res);
                    stack_num[++top_num] = res; //将计算结果入栈  
            }
            
        }
       
    }
    return stack_num[top_num];
}

