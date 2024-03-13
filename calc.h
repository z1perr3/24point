#ifndef __CALC_H__
#define __CALC_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>

int Precede(char a,char b);  //比较运算符a和b的优先级。如果a > b 返回 1；a == b 返回0；a<b 返回-1
double yunsuan(double a,double b,char op);  //两个运算数之间的四则运算
double jisuan(char *ch); //计算字符串ch的值

#endif

