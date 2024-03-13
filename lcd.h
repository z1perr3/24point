#ifndef __LCD_H__
#define __LCD_H__
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

int lcd_init(void); //初始化LCD屏：打开和映射LCD屏幕文件
void lcd_uninit(void);//释放LCD屏：接触映射，关闭LCD屏幕文件
void lcd_draw_point(int x,int y,int color); //画点函数，用来将坐标为(x,y)的像素点显示为color色
void lcd_draw_clear(int x0,int y0,int w,int h,int color);//清屏函数，用来将从(x0,y0)为起点，宽w，高h的矩形区域显示为 color色
void lcd_draw_rectangle(int x0, int y0, int w, int h, int color);
void lcd_draw_triangle(int y1,int y2,int x,int w,int mod,int color);
void lcd_draw_ellipse(int x0,int y0,int a,int b,int color);
void lcd_draw_circle(int x0,int y0,int r,int color);

void lcd_draw_diamonds(int x0,int y0,int size,int color);
void lcd_draw_spade(int x0,int y0,int size,int color);//画黑桃
void lcd_draw_hearts(int x0,int y0,int size,int color);
void lcd_draw_club(int x0,int y0,int size,int color);




void draw_UI0(void);//画主菜单
void draw_UI1(); //画练习模式

void lcd_draw_word(int x0,int y0,int w,int h,char *data,int color);


#endif
