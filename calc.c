#include "calc.h"
double stack_num[20];  //������ջ
char stack_op[20];  //�����ջ
int top_num,top_op = -1;  //ջ��λ��
int Precede(char a,char b)  //�Ƚ������a��b�����ȼ������a > b ���� 1��a == b ����0��a<b ����-1
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

double yunsuan(double a,double b,char op)  //����������֮�����������
{
    double r;
    if(op == '+') r = a+b;
    if(op == '-') r = a-b;
    if(op == '*') r = a*b;
    if(op == '/') r = a/b;
    return r;
}

double jisuan(char *ch) //�����ַ���ch��ֵ
{
    int i = 1;
    int num;
    double num1,num2;
    char op;
    double res;
    stack_op[++top_op] = '#'; //����'#'��ջ
    while(ch[i] != '\0')
    {
        if(ch[i] >= 48 && ch[i] <= 57)  //˵��������
        {
            num = ch[i] - 48;
            stack_num[++top_num] = num; //��ջ
            i++;
        }
        else  //˵�����������
        {

            if(Precede(stack_op[top_op],ch[i]) == -1)  //���ȼ���ջ��Ԫ�ش�
            {
                stack_op[++top_op] = ch[i];
                i++;
                 //printf("ջ��Ԫ��Ϊ��%.2f\n",stack_num[top_num]);
            }
            else if(Precede(stack_op[top_op],ch[i]) == 0) //���ȼ����
            {
                top_op --; //��ջ
                i++;
            }  
            else  if(Precede(stack_op[top_op],ch[i]) == 1)
            {
                    
                    num1 = stack_num[top_num--]; //ȡջ��Ԫ�أ���ջ
                    num2 = stack_num[top_num--];//ȡջ��Ԫ�أ���ջ
                    op = stack_op[top_op--]; //ȡջ��Ԫ�أ���ջ
                   // printf("%c\n",op);
                    res = yunsuan(num2,num1,op);
                    //printf("num2 = %.2f,num1 = %.2f,op = %c,res=%.2f\n",num2,num1,op,res);
                    stack_num[++top_num] = res; //����������ջ  
            }
            
        }
       
    }
    return stack_num[top_num];
}

