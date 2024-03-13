#ifndef __LCD_H__
#define __LCD_H__
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

int lcd_init(void); //��ʼ��LCD�����򿪺�ӳ��LCD��Ļ�ļ�
void lcd_uninit(void);//�ͷ�LCD�����Ӵ�ӳ�䣬�ر�LCD��Ļ�ļ�
void lcd_draw_point(int x,int y,int color); //���㺯��������������Ϊ(x,y)�����ص���ʾΪcolorɫ
void lcd_draw_clear(int x0,int y0,int w,int h,int color);//������������������(x0,y0)Ϊ��㣬��w����h�ľ���������ʾΪ colorɫ
void lcd_draw_rectangle(int x0, int y0, int w, int h, int color);
void lcd_draw_triangle(int y1,int y2,int x,int w,int mod,int color);
void lcd_draw_ellipse(int x0,int y0,int a,int b,int color);
void lcd_draw_circle(int x0,int y0,int r,int color);

void lcd_draw_diamonds(int x0,int y0,int size,int color);
void lcd_draw_spade(int x0,int y0,int size,int color);//������
void lcd_draw_hearts(int x0,int y0,int size,int color);
void lcd_draw_club(int x0,int y0,int size,int color);




void draw_UI0(void);//�����˵�
void draw_UI1(); //����ϰģʽ

void lcd_draw_word(int x0,int y0,int w,int h,char *data,int color);


#endif
