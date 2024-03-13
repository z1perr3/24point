#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"
#include "input.h"
#include "calc.h"
#include<time.h>


extern unsigned char mod_num[10][16/8*33];
int UI_mod =0; //表示页面的标识符  0:表示在主界面 1：练习界面 2：挑战界面
char expression[15] = {0}; // 存储的表达式
int exp_index = 0; //表达式下标，计数
int res;
int card[4] = {0};
int i,j;

void exec_prac()    //执行进入练习模式
{
	UI_mod = 1;
	exp_index = 0;
	memset(expression,0,sizeof(expression));

	//随机数
	srand((unsigned int)time(NULL));
	for (i=0; i < 4; ++i)
		{
		card[i]=rand()%9+1;
		}
	 
	draw_UI1();
}


void exec_chal()//执行进入挑战模式
{
    UI_mod = 2;
    exp_index = 0;
	memset(expression,0,sizeof(expression));

	//随机数
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
	draw_UI0(); //画主菜单
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

