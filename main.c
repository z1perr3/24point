#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"
#include "input.h"
#include "calc.h"
#include<time.h>


extern unsigned char mod_num[10][16/8*33];
int UI_mod =0; //��ʾҳ��ı�ʶ��  0:��ʾ�������� 1����ϰ���� 2����ս����
char expression[15] = {0}; // �洢�ı��ʽ
int exp_index = 0; //���ʽ�±꣬����
int res;
int card[4] = {0};
int i,j;

void exec_prac()    //ִ�н�����ϰģʽ
{
	UI_mod = 1;
	exp_index = 0;
	memset(expression,0,sizeof(expression));

	//�����
	srand((unsigned int)time(NULL));
	for (i=0; i < 4; ++i)
		{
		card[i]=rand()%9+1;
		}
	 
	draw_UI1();
}


void exec_chal()//ִ�н�����սģʽ
{
    UI_mod = 2;
    exp_index = 0;
	memset(expression,0,sizeof(expression));

	//�����
	srand((unsigned int)time(NULL));
	for (i=0; i < 4; ++i)
		{
		card[i]=rand()%9+1;
		}
	
   draw_UI2();
}

void exec_door()
{
   UI_mod = 0;
    exp_index = 0;
	memset(expression,0,sizeof(expression));
   draw_UI0();
}

int main()
{
	lcd_init();
	draw_UI0(); //�����˵�
	while(1)
	{
		res = get_input_event();
		input_process(res);
	}
	/*
    char ch[] = "#(1+2)*5#";
    printf("%d\n",Precede('(',')'));
    int sum = jisuan(ch);
    printf("%d\n",res);
    return 0;
   */
	lcd_uninit();
	return 0;
}

