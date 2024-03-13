#include "lcd.h"
#include "model.h"
extern unsigned char word_big[5][96/8*99];
extern unsigned char word_min[][32/8*32];
extern unsigned char mod_char[][16/8*33];

extern int card[4];

int lcdfd; //����LCD��Ļ�ļ����ļ�������
int *plcd; //����LCD��Ļӳ���ڴ��׵�ַ
int yellow = 0xffff00;
int gree = 0x7fff00;
int black = 0x707070;
int white = 0xffffff;
int red = 0xff0000;

/*
	lcd_init����ʼ��lcd����������lcd���ļ���ӳ��
		@����ֵ��
			��ʼ��ʧ�ܣ�-1 ����ӡʧ����Ϣ
			�ɹ���1
*/
int lcd_init()
{

	lcdfd = open("/dev/fb0",O_RDWR);
	if(-1 == lcdfd)
	{
		perror("open lcd error");
		return -1;
	}

	/* ��LCD��ӳ�䵽�ڴ�ռ� =��Frame Buffer ֡�����豸*/
	plcd = (int*)mmap(NULL,//ϵͳ�Զ�ѡ��ӳ���ַ
						800*480*32/8,	//ӳ��ռ��С����λ �ֽڣ�����Ļ800*480�����ص㣬ÿ�����ص�32λ��32/8���ֽڣ�
						PROT_READ|PROT_WRITE,//�߱���дȨ��
						MAP_SHARED,//����ӳ�䣬��ӳ���ڴ�ռ�Ĳ����ᱻͬ�����ļ�
						lcdfd,//ָ��ӳ����ļ�
						0); //���ļ�ͷ��ʼӳ��
	if(MAP_FAILED == plcd)
	{
		perror("mmap lcd error");
		close(lcdfd);
		return -1;
	}
}



/*
	lcd_unint(void):�ر��ļ��ͽ��ӳ��
	
*/

void lcd_uninit(void)
{
	munmap(plcd,800*480*32/8);
	close(lcdfd);
}


/*
	@lcd_draw_point���ڵ㣨x��y�������colorɫ
*/
void lcd_draw_point(int x,int y,int color)
{
	*(plcd+y*800+x) = color;
}


/*
	lcd_draw_clear����ָ����ɫ���lcdָ����С����Ļ
	@x0:��ʼx������
	@y0����ʼy������
	@w�����
	@h���߶�
	@color��ָ��������ɫ
*/
void lcd_draw_clear(int x0,int y0,int w,int h,int color)
{
	int x, y;
	for(y = y0;y < y0 + h; y++)
	{
		for(x = x0;x < x0+w;x++)
		{
			*(plcd+y*800+x) = color;
		}
	}
}

/*
	lcd_draw_rectangle��������
		@ x0:
		@ y0:���ĵ�����
		@ w:���
		@ h:�߶�
		@color:��ɫֵ
*/
void lcd_draw_rectangle(int x0, int y0, int w, int h, int color)
{

	int x, y;

	for (y = y0-h/2; y < y0 + h/2; y++)
	{
		for (x = x0-w/2; x < x0 + w/2; x++)
		{
			lcd_draw_point(x, y  , color);
		}
	}
}


/*
	lcd_draw_trangle: ����Ļ�ϻ�һ��ֱ�������Σ�������
		color������ɫ���þ��Ρ�
	@y1: �������θߵĽ�С����
	@y2: �������θߵĽϴ�����
	@w:  �������εĿ�>0���ң�<0����
	@mod: mod>0���㳯�ϣ�mod<0���㳯��
	@color:��ֱ��������Ҫ���ı�ɫֵ
	@����ֵ:
		�޷���ֵ��		
*/
void lcd_draw_triangle(int y1,int y2,int x,int w,int mod,int color)
{
	
	int i,j,h=y2-y1;
	for(i=0;i<=abs(w);i++)
	{
		for(j=h;j>=0;j--)
		{
			if(w>0)
			{
				if(j <= 1.0*(w-i)*h/w)
				{
					if(mod==0)//0Ϊ�������ϣ�1Ϊ��������
						lcd_draw_point(x+i,y2-j,color);
					else
						lcd_draw_point(x+i,y1+j,color); 
				}
			}
			else
			{
				if(j <= 1.0*abs(w+i)*h/(-w))
				{
					if(mod==0)
						lcd_draw_point(x-i,y2-j,color);
					else
						lcd_draw_point(x-i,y1+j,color);
				}
			}
		}
	}
}


/*
	lcd_draw_circle����Բ
		@ x0:
		@ y0: Բ������
		@ r: �뾶
		@ color:��ɫֵ
*/
void lcd_draw_circle(int x0,int y0,int r,int color)//��Բ
{
	int i,j;
	for(i=x0-r;i<=x0+r;i++)
	{
		for(j=y0-r;j<=y0+r;j++)
		{
			if((i-x0)*(i-x0) + (j-y0)*(j-y0) <= r*r)
			{
				lcd_draw_point(i,j,color);
			}
		}
	}
}


/*
	lcd_draw_ellipse������Բ
	@x0
	@y0  ---->Բ������
	@a ��
	@b ��
	@color��Ҫ������ɫ
*/
void lcd_draw_ellipse(int x0,int y0,int a,int b,int color)//����Բ
{
	int i,j;
	for(i=x0-a;i<=x0+a;i++)
	{
		for(j=y0-b;j<=y0+b;j++)
		{
			if(1.0*(i-x0)*(i-x0)/(a*a) + 1.0*(j-y0)*(j-y0)/(b*b) <= 1)
			{
				lcd_draw_point(i,j,color);
			}
		}
	}
}


void lcd_draw_diamonds(int x0,int y0,int size,int color)//������
{
	lcd_draw_triangle(y0-2*size,y0,x0,1.2*size,0,color);//����
	lcd_draw_triangle(y0-2*size,y0,x0,-1.2*size,0,color);//����
	lcd_draw_triangle(y0,y0+2*size,x0,1.2*size,1,color);//����
	lcd_draw_triangle(y0,y0+2*size,x0,-1.2*size,1,color);//����
} 

void lcd_draw_spade(int x0,int y0,int size,int color)//������
{
	//����3Ϊ1.732
	lcd_draw_triangle(y0-2*size,y0,x0,1.732*size,0,color);//����
	lcd_draw_triangle(y0-2*size,y0,x0,-1.732*size,0,color);//����
	lcd_draw_triangle(y0,y0+size,x0,1.732*size,1,color);//����
	lcd_draw_triangle(y0,y0+size,x0,-1.732*size,1,color);//����
	
	lcd_draw_circle(x0-0.866*size,y0+0.5*size,size,color);
	lcd_draw_circle(x0+0.866*size,y0+0.5*size,size,color);
	
	lcd_draw_triangle(y0+size,y0+2*size,x0,size/1.5,0,color);//����
	lcd_draw_triangle(y0+size,y0+2*size,x0,-size/1.5,0,color);//����	
}

void lcd_draw_hearts(int x0,int y0,int size,int color)//������
{
	lcd_draw_triangle(y0,y0+2*size,x0,1.732*size,1,color);//����
	lcd_draw_triangle(y0,y0+2*size,x0,-1.732*size,1,color);//����
	lcd_draw_triangle(y0-size,y0,x0,1.732*size,0,color);//����
	lcd_draw_triangle(y0-size,y0,x0,-1.732*size,0,color);//����
	
	lcd_draw_circle(x0-0.866*size,y0-0.5*size,size,color);
	lcd_draw_circle(x0+0.866*size,y0-0.5*size,size,color);
}

void lcd_draw_club(int x0,int y0,int size,int color)//��÷��
{
	lcd_draw_circle(x0,y0-size,size,color);
	lcd_draw_rectangle(x0,y0,size/2,2*size,color);
	lcd_draw_circle(x0-size-size/4,y0+size/4,size,color);
	lcd_draw_circle(x0+size+size/4,y0+size/4,size,color);
	
	lcd_draw_triangle(y0+size/2,y0+2*size,x0,size,0,color);//����
	lcd_draw_triangle(y0+size/2,y0+2*size,x0,-size,0,color);//����
}


/*
	lcd_draw_word��������
	@ x0:
	@ y0:��ʼ����
	@ w:���
	@ h���߶�
	@ data����������
	@ color����ʾ��ɫ
*/
void lcd_draw_word(int x0,int y0,int w,int h,char *data,int color)
{
	int i,k;
	
	for(i=0;i<w*h/8;i++)
	{
		for(k=0;k<8;k++)
		{
			if((data[i]<<k )&0x80)
			{
				lcd_draw_point(x0+((i*8+k)>w?(i*8+k)%w:(i*8+k)),y0+i/(w/8),color);
			}
		}			
	}
}




//�����˵�
void draw_UI0()
{
	int i;
	lcd_draw_rectangle(400, 240, 800,480,0xc6e2ff);//������
	
	lcd_draw_rectangle(400, 150, 400,200,0x00FFF);//���ı���
	lcd_draw_triangle(50,250,200,-100,0,0x00FFF);//����
	lcd_draw_triangle(50,250,600,100,1,0x00FFF);//����
	
	lcd_draw_word(100,150,96,99,word_big[0],0x121212);//��
	lcd_draw_word(200,150,96,99,word_big[1],0x121212);//��
	lcd_draw_word(350,150,96,99,word_big[2],0x121212);//2
	lcd_draw_word(400,150,96,99,word_big[3],0x121212);//4
	lcd_draw_word(500,150,96,99,word_big[4],0x121212);//��
	
	lcd_draw_spade(300,300,10,0x121212);//������
	lcd_draw_hearts(300,400,10,0xEE4000);//������

    //lcd_draw_rectangle(65,380,35,35, 0xcd1076);//�����ؼ�

	for(i=0;i<4;i++)
	{
		lcd_draw_word(350+i*50,300,32,32,word_min[i],0x121212);//��ϰģʽ
		lcd_draw_word(350+i*50,400,32,32,word_min[4+i],0x121212);//��սģʽ
	}	
}







//����ϰģʽ����
void draw_UI1()
{
	int i;
	lcd_draw_rectangle(400, 240, 800,480,0x7b68ee);//������
	for(i=0;i<4;i++)
	{
		lcd_draw_rectangle(100+i*200, 150, 120,168, 0xFFFFFF);//����
	}
	
	lcd_draw_diamonds(100,150,10,0xEE4000);//������
	lcd_draw_spade(300,150,10,0x121212);//������
	lcd_draw_hearts(500,150,10,0xEE4000);//������
	lcd_draw_club(700,150,10,0x121212);//��÷��

	lcd_draw_word(45,70,16,33,mod_num[card[0]],0xff0000);
	lcd_draw_word(45+200,70,16,33,mod_num[card[1]],0x000000);
	lcd_draw_word(45+400,70,16,33,mod_num[card[2]],0xff0000);
	lcd_draw_word(45+600,70,16,33,mod_num[card[3]],0x00000);
	for(i=0;i<6;i++)//�������
	{
		lcd_draw_rectangle(260+i*60+8,315,50,40,  0x9b78b2);
	}
	lcd_draw_word(260,300,16,33,mod_char['+'-40],0x000000);
	lcd_draw_word(320,300,16,33,mod_char['-'-40],0x000000);
	lcd_draw_word(380,300,16,33,mod_char['*'-40],0x000000);
	lcd_draw_word(440,300,16,33,mod_char['/'-40],0x000000);
	lcd_draw_word(500,300,16,33,mod_char['('-40],0x000000);
	lcd_draw_word(560,300,16,33,mod_char[')'-40],0x000000);
	
	lcd_draw_rectangle(415,400,480,100, 0xFFFFFF);//��������
	//lcd_draw_rectangle(65,380,35,35, 0xcd1076);//�����ؼ�

	lcd_draw_ellipse(95,375,50,17,0x0000ee);//�����ؼ�
	lcd_draw_word(65,355,16,33,letter['b'-97],0x121212);
	lcd_draw_word(83,355,16,33,letter['a'-97],0x121212);
	lcd_draw_word(101,355,16,33,letter['c'-97],0x121212);
	lcd_draw_word(119,355,16,33,letter['k'-97],0x121212);
	
	lcd_draw_ellipse(710,320,50,17,0x0000ee);//���ύ��ť
	lcd_draw_word(660,300,16,33,letter['s'-97],0x121212);
	lcd_draw_word(678,300,16,33,letter['u'-97],0x121212);
	lcd_draw_word(696,300,16,33,letter['b'-97],0x121212);
	lcd_draw_word(714,300,16,33,letter['m'-97],0x121212);
	lcd_draw_word(732,300,16,33,letter['i'-97],0x121212);
	lcd_draw_word(750,300,16,33,letter['t'-97],0x121212);
	
	lcd_draw_ellipse(710,370,50,17,0x0000ee);//�������ť
	lcd_draw_word(670,350,16,33,letter['c'-97],0x121212);
	lcd_draw_word(688,350,16,33,letter['l'-97],0x121212);
	lcd_draw_word(706,350,16,33,letter['e'-97],0x121212);
	lcd_draw_word(724,350,16,33,letter['a'-97],0x121212);
	lcd_draw_word(744,350,16,33,letter['r'-97],0x121212);

	lcd_draw_ellipse(710,420,50,17,0x0000ee);//����һ�ⰴť
	lcd_draw_word(680,400,16,33,letter['n'-97],0x121212);
	lcd_draw_word(698,400,16,33,letter['e'-97],0x121212);
	lcd_draw_word(716,400,16,33,letter['x'-97],0x121212);
	lcd_draw_word(734,400,16,33,letter['t'-97],0x121212);
		
}

//����սģʽ����
void draw_UI2()
{
	int i;
	lcd_draw_rectangle(400, 240, 800,480, 0x87cefa);//������
	for(i=0;i<4;i++)
	{
		lcd_draw_rectangle(100+i*200, 150, 120,168, 0xFFFFFF);//����
	}
	
	lcd_draw_diamonds(100,150,10,0xEE4000);//������
	lcd_draw_spade(300,150,10,0x121212);//������
	lcd_draw_hearts(500,150,10,0xEE4000);//������
	lcd_draw_club(700,150,10,0x121212);//��÷��

	lcd_draw_word(45,70,16,33,mod_num[card[0]],0xff0000);
	lcd_draw_word(45+200,70,16,33,mod_num[card[1]],0x000000);
	lcd_draw_word(45+400,70,16,33,mod_num[card[2]],0xff0000);
	lcd_draw_word(45+600,70,16,33,mod_num[card[3]],0x000000);
	
	for(i=0;i<6;i++)//�������
	{
		lcd_draw_rectangle(260+i*60+8,315,50,40, 0x4a4a7f);
	}
	lcd_draw_word(260,300,16,33,mod_char['+'-40],0x000000);
	lcd_draw_word(320,300,16,33,mod_char['-'-40],0x000000);
	lcd_draw_word(380,300,16,33,mod_char['*'-40],0x000000);
	lcd_draw_word(440,300,16,33,mod_char['/'-40],0x000000);
	lcd_draw_word(500,300,16,33,mod_char['('-40],0x000000);
	lcd_draw_word(560,300,16,33,mod_char[')'-40],0x000000);
	
	lcd_draw_rectangle(415,400,480,100, 0xFFFFFF);//��������
	//lcd_draw_rectangle(65,380,35,35, 0xcd1076);//�����ؼ�

	lcd_draw_ellipse(95,375,50,17,0x0000ee);//�����ؼ�
	lcd_draw_word(65,355,16,33,letter['b'-97],0x121212);
	lcd_draw_word(83,355,16,33,letter['a'-97],0x121212);
	lcd_draw_word(101,355,16,33,letter['c'-97],0x121212);
	lcd_draw_word(119,355,16,33,letter['k'-97],0x121212);
	
	lcd_draw_ellipse(710,320,50,17,0x0000ee);//���ύ��ť
	lcd_draw_word(660,300,16,33,letter['s'-97],0x121212);
	lcd_draw_word(678,300,16,33,letter['u'-97],0x121212);
	lcd_draw_word(696,300,16,33,letter['b'-97],0x121212);
	lcd_draw_word(714,300,16,33,letter['m'-97],0x121212);
	lcd_draw_word(732,300,16,33,letter['i'-97],0x121212);
	lcd_draw_word(750,300,16,33,letter['t'-97],0x121212);
	
	lcd_draw_ellipse(710,370,50,17,0x0000ee);//�������ť
	lcd_draw_word(670,350,16,33,letter['c'-97],0x121212);
	lcd_draw_word(688,350,16,33,letter['l'-97],0x121212);
	lcd_draw_word(706,350,16,33,letter['e'-97],0x121212);
	lcd_draw_word(724,350,16,33,letter['a'-97],0x121212);
	lcd_draw_word(744,350,16,33,letter['r'-97],0x121212);

	lcd_draw_ellipse(710,420,50,17,0x0000ee);//����һ�ⰴť
	lcd_draw_word(680,400,16,33,letter['n'-97],0x121212);
	lcd_draw_word(698,400,16,33,letter['e'-97],0x121212);
	lcd_draw_word(716,400,16,33,letter['x'-97],0x121212);
	lcd_draw_word(734,400,16,33,letter['t'-97],0x121212);
		
}


