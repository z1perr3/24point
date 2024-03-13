#include "input.h"
#include "lcd.h"
#include "calc.h"
extern int UI_mod;
extern char expression[10];
extern int exp_index;
extern int card[4];
extern unsigned char mod_num[10][16/8*33];
extern unsigned char mod_char[][16/8*33];
int count1[4]={0};
int count2[4]={0};
int sum;
int sum2;
int ord=0;
char ex1[];
char ex2[];



int get_input_event(void)
{
	int event_fd;
	struct input_event ev;
	int rsize;
	int pos_x,pos_y; //�������µ�����
	int x = -1,y = -1; //���ص��µ�����
	event_fd = open("/dev/input/event0",O_RDWR);
	int count=0;
	
	if(-1 == event_fd)
	{
		perror("open file error!");
		return -1;
	}
	while(1)
	{
		rsize = read(event_fd,&ev,sizeof(ev));
		if(-1 == rsize)
		{
			return -1;
		}
		
		if (ev.type == EV_ABS && ev.code == ABS_X)
		{
			pos_x = ev.value;
		}
		if (ev.type == EV_ABS && ev.code == ABS_Y)
		{
			pos_y = ev.value;
		}

		//��������С1024*800,��ʾ�������ص㣩��С 800*480
		x = pos_x *800/1024;
		y = pos_y *480/600;
		if(ev.type == EV_KEY && ev.code == BTN_TOUCH &&
		ev.value == 0)  //һ�δ�������
		{
			printf("x:%d,y:%d\n",x,y); 
			if(UI_mod == 0 ) //���˵�������
			{
				if(x >= 300 && x<= 500 && y>= 300 && y<=332) //��ʾ�����ˡ���ϰģʽ��
				{
					return PRACTICE_MODE;
				}
				if(x >= 300 && x<= 500 && y>= 410 && y<=450)//��ʾ�����ˡ���սģʽ��
				{
					return CHALENGE_MODE;
				}
			}
			if(UI_mod == 1 ) //��ϰģʽ����
			{
				if(x >= 40 && x<= 160 && y>= 66 && y<=234)  //��ʾ�����˵�һ����
				{
					return CARD_1;
				}
				if(x >= 240 && x<= 360 && y>= 66 && y<=234)  //��ʾ�����˵ڶ�����
				{
					return CARD_2;
				}
				if(x >= 445 && x<= 564 && y>= 66 && y<=234)  //��ʾ�����˵�������
				{
					return CARD_3;
				}
				if(x >= 650 && x<=770 && y>= 66 && y<=234)  //��ʾ�����˵�������
				{
					return CARD_4;
				}
				if(x >= 245 && x<= 280 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�+��
				{
					return ADD;
				}
				if(x >=310  && x<= 353 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�-��
				{
					return SUB;
				}
				if(x >= 375 && x<= 410 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�*��
				{
					return MUL;
				}
				if(x >= 430 && x<= 475 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�/��
				{
					return DIV;
				}
				if(x >= 490 && x<= 535 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�(��
				{
					return LBR;
				}
				if(x >= 550 && x<= 600 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�)��
				{
					return RBR;
				}
				if(x >= 65 && x<= 100 && y>=380  && y<=410) //��ʾ��ѡ���ˡ�back��
				{
					return Back;
				}
				if(x >= 690 && x<= 740 && y>=365  && y<=385) //��ʾ��ѡ���ˡ�clear��
				{
					return CLEAR;
				}
				if(x >= 690 && x<= 740 && y>=410  && y<=450) //��ʾ��ѡ���ˡ�next��
				{
					return next;
				}
				if(x >= 690 && x<= 740 && y>=310  && y<=335) //��ʾ��ѡ���ˡ�submit��
				{
					return submit;
				}
			}
			
			if(UI_mod == 2 ) //��սģʽ����
			{
				if(x >= 40 && x<= 160 && y>= 66 && y<=234)  //��ʾ�����˵�һ����
				{
					return CARD_1;
				}
				if(x >= 240 && x<= 360 && y>= 66 && y<=234)  //��ʾ�����˵ڶ�����
				{
					return CARD_2;
				}
				if(x >= 445 && x<= 564 && y>= 66 && y<=234)  //��ʾ�����˵�������
				{
					return CARD_3;
				}
				if(x >= 650 && x<=770 && y>= 66 && y<=234)  //��ʾ�����˵�������
				{
					return CARD_4;
				}
				if(x >= 245 && x<= 280 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�+��
				{
					return ADD;
				}
				if(x >=310  && x<= 353 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�-��
				{
					return SUB;
				}
				if(x >= 375 && x<= 410 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�*��
				{
					return MUL;
				}
				if(x >= 430 && x<= 475 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�/��
				{
					return DIV;
				}
				if(x >= 490 && x<= 535 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�(��
				{
					return LBR;
				}
				if(x >= 550 && x<= 600 && y>=300  && y<=325) //��ʾ��ѡ���ˡ�)��
				{
					return RBR;
				}
				if(x >= 690 && x<= 740 && y>=365  && y<=385) //��ʾ��ѡ���ˡ�clear��
				{
					return CLEAR;
					
				}
				if(x >= 65 && x<= 100 && y>=380  && y<=410) //��ʾ��ѡ���ˡ�back��
				{
					return Back;
				}
				if(x >= 690 && x<= 740 && y>=410  && y<=450) //��ʾ��ѡ���ˡ�next��
					{
					return next;
					}
				if(x >= 690 && x<= 740 && y>=310  && y<=335) //��ʾ��ѡ���ˡ�submit��
				{
					return submit;
				}
				}
			}
		}
	close(event_fd);
	}


void input_process(int value)
{
	int res = value;
	//int count1[4]={0};
	if(UI_mod == 0) //���˵�
	{
		if(res == PRACTICE_MODE)  //��ʾ��������ϰģʽ
		{
			exec_prac();
		}
		if(res == CHALENGE_MODE)  //��ʾ����ѵ��ģʽ
		{
			exec_chal();
		}
	}
	if(UI_mod == 1) // ��ϰģʽ�˵�
		{
		
		    if(res == next)  //��ʾ������ˢ��
		    	{
		    	exec_prac();
			   count1[0]=0;
	           count1[1]=0;
	           count1[2]=0;
	           count1[3]=0;
		    	}
			 if(res == Back)  //��ʾ�����˷������˵�
		        {
				exec_door();
		        }

			 
			 if(res == CARD_1||res == CARD_2||res == CARD_3||res == CARD_4)
			 {
			    if(res == CARD_1&&count1[0]<1)
			  {
				expression[exp_index] = card[0] + '0';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[card[0]],0x000000);
				exp_index++;
				count1[0]=1;
			  }
			if(res == CARD_2&&count1[1]<1)
			  {
				expression[exp_index] = card[1] + '0';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[card[1]],0x000000);
				exp_index++;
				count1[1]=1;
			  }
			if(res == CARD_3&&count1[2]<1)
			  {
				expression[exp_index] = card[2] + '0';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[card[2]],0x000000);
				exp_index++;
				count1[2]=1;
			  }
			if(res == CARD_4&&count1[3]<1)
			  {
				expression[exp_index] = card[3] + '0';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[card[3]],0x000000);
				exp_index++;	
				count1[3]=1;
			   }
			 	}
			 if(res == submit)
			{
			    printf("%d\n",exp_index);
			    //expression[exp_index] = card[0] + '1';
				for (int p = 0;  p < exp_index+2; p++)
					{
					if(p==0||p==exp_index+1)
						{ex1[p]='#';}
					else{ex1[p]=expression[p-1];}
					}
				printf("%s\n",expression);
				printf("%s\n",ex1);
				int sum=jisuan(ex1);
				if (sum==24)
					{
					int s1=sum/10;
				int s2=sum%10;
				printf("%d\n",sum,s1,s2);
				
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[8],0x000000);
				exp_index++;
				//lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[sum],0x000000);
				
				exp_index++;
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[s1],0x000000);
				exp_index++;
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[s2],0x000000);
				exp_index++;
					}
				else{
					lcd_draw_rectangle(415,400,480,100, 0xffffff);
				exp_index=0;
					count1[0]=0;
	                count1[1]=0;
	                count1[2]=0;
	                count1[3]=0;
					}
			}


			 
			if(res == ADD)
			{
				expression[exp_index] = '+';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[3],0x000000);
				exp_index++;	
			}
			
			if(res == SUB)
			{
				
				expression[exp_index] = '-';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[5],0x000000);
				exp_index++;	
			}
			if(res == MUL)
			{
				expression[exp_index] = '*';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[2],0x000000);
				exp_index++;	
			}
			if(res == DIV)
			{
				expression[exp_index] = '/';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[7],0x000000);
				exp_index++;	
			}
			if(res == LBR)
			{
				expression[exp_index] = '(';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[0],0x000000);
				exp_index++;
			}
			if(res == RBR)
			{
				
				expression[exp_index] = ')';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[1],0x000000);
				exp_index++;	
			}
			if(res == CLEAR)
			{
				lcd_draw_rectangle(415,400,480,100, 0xffffff);
				exp_index=0;
					count1[0]=0;
	                count1[1]=0;
	                count1[2]=0;
	                count1[3]=0;
			}
			
		}
	if(UI_mod == 2) // ��սģʽ�˵�
		{
		    if(res == Back)  //��ʾ�����˷������˵�
		{
			exec_door();
		}
			if(res == next)  //��ʾ������ˢ��
		    {
		 	   exec_chal();
			   count1[0]=0;
	           count1[1]=0;
	           count1[2]=0;
	           count1[3]=0;
		    }
			
			if(res == CARD_1||res == CARD_2||res == CARD_3||res == CARD_4)
			 {
			    if(res == CARD_1&&count2[0]<1)
			  {
				expression[exp_index] = card[0] + '0';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[card[0]],0x000000);
				exp_index++;
				count2[0]=1;
			  }
			if(res == CARD_2&&count2[1]<1)
			  {
				expression[exp_index] = card[1] + '0';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[card[1]],0x000000);
				exp_index++;
				count2[1]=1;
			  }
			if(res == CARD_3&&count2[2]<1)
			  {
				expression[exp_index] = card[2] + '0';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[card[2]],0x000000);
				exp_index++;
				count2[2]=1;
			  }
			if(res == CARD_4&&count2[3]<1)
			  {
				expression[exp_index] = card[3] + '0';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[card[3]],0x000000);
				exp_index++;	
				count2[3]=1;
			   }
			 	}
			if(res == ADD)
			{
				
				expression[exp_index] = '+';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[3],0x000000);
				exp_index++;	
			}
			if(res == SUB)
			{
				
				expression[exp_index] = '-';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[5],0x000000);
				exp_index++;	
			}
			if(res == MUL)
			{
				expression[exp_index] = '*';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[2],0x000000);
				exp_index++;	
			}
			if(res == DIV)
			{
				expression[exp_index] = '/';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[7],0x000000);
				exp_index++;	
			}
			if(res == LBR)
			{
				
				expression[exp_index] = '(';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[0],0x000000);
				exp_index++;	
			}
			if(res == RBR)
			{
				
				expression[exp_index] = ')';
				printf("exp:%s\n",expression);
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[1],0x000000);
				exp_index++;	
			}
			if(res == CLEAR)
			{
				lcd_draw_rectangle(415,400,480,100, 0xffffff);
				exp_index=0;
				count2[0]=0;
	            count2[1]=0;
	            count2[2]=0;
	            count2[3]=0;
			}
			if(res == submit)
			{
			    printf("%d\n",exp_index);
			    //expression[exp_index] = card[0] + '1';
				for (int f = 0;  f < exp_index+2; f++)
					{
					if(f==0||f==exp_index+1)
						{ex2[f]='#';}
					else{ex2[f]=expression[f-1];}
					}
				printf("%s\n",expression);
				printf("%s\n",ex2);
				int sum2=jisuan(ex2);
				if (sum2==24)
					{
				     int s1=sum2/10;
				     int s2=sum2%10;
				     printf("%d\n,%d\n,%d\n",sum2,s1,s2);
		
				     lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[8],0x000000);
				     exp_index++;
				     //lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[sum2],0x000000);
				
				     exp_index++;
				     lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[s1],0x000000);
				     exp_index++;
				     lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[s2],0x000000);
				     exp_index++;
					}
				else{
					lcd_draw_rectangle(415,400,480,100, 0xffffff);
				    exp_index=0;
					count1[0]=0;
	                count1[1]=0;
	                count1[2]=0;
	                count1[3]=0;
					}
			}

			/*ԭʼ���룺
			 if(res == submit)
			{
			    printf("%d\n",exp_index);
			    //expression[exp_index] = card[0] + '1';
				for (int f = 0;  f < exp_index+2; f++)
					{
					if(f==0||f==exp_index+1)
						{ex2[f]='#';}
					else{ex2[f]=expression[f-1];}
					}
				printf("%s\n",expression);
				printf("%s\n",ex2);
				int sum2=jisuan(ex2);
				if (sum2==24)
					{
					int s1=sum2/10;
				int s2=sum2%10;
				printf("%d\n",sum2,s1,s2);
				
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_char[8],0x000000);
				exp_index++;
				//lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[sum2],0x000000);
				
				exp_index++;
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[s1],0x000000);
				exp_index++;
				lcd_draw_word(200+30 * exp_index,400,16,33,mod_num[s2],0x000000);
				exp_index++;
					}
				else{
					lcd_draw_rectangle(415,400,480,100, 0xffffff);//ˢ�´�����
				exp_index=0;
					count1[0]=0;
	                count1[1]=0;
	                count1[2]=0;
	                count1[3]=0;
					}
			}*/
		}
	
}
