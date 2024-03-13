#ifndef __INPUT_H__
#define __INPUT_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>

#define PRACTICE_MODE 1
#define CHALENGE_MODE 2
#define CARD_1 3
#define CARD_2 4
#define CARD_3 5
#define CARD_4 6
#define ADD 7
#define SUB 8
#define MUL 9
#define DIV 10
#define LBR 11
#define RBR 12
#define CLEAR 13
#define Back 14
#define next 15
#define submit 16
int get_input_event(void);
void input_process(int value);
#endif