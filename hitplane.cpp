#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define N 35
void print(int [][N]);//�������
void movebul(int [][N]);//�ӵ��ƶ�����
void movepla(int [][N]);//�л��ƶ�����
void setting(void);//���ú���
void menu(void);//�˵�����
int scr[22][N]={0},pl=9,width=24,speed=3,density=30,score=0,death=0;
/*ȫ�ֱ��������桢�һ���ʼλ�������ȡ��л��ٶȡ��л��ܶȡ��÷֡�����*/
int main()
{
menu();
int i=0,j=0;
scr[21][pl]=1;
scr[0][5]=3;
while(1)/*always loop*/
{
	if(kbhit())/*Check whether the button is pressed,if pressed return 1��else return 0,press any key to enter the game */
		switch(getch())//���������ƶ��ͽ���˵�
		{
			 case (75):case 'A':
			 	if(pl>0)/*On the right side of the left edge */
				 	scr[21][pl]=0,scr[21][--pl]=1;
					 /*at first ,the 21 lines are all 0 except the middle position is 1,then Where there is the plane , there is 1. */
					break;
					/*Equivalent code:
                    scr[21][pl]=0;
                    pl--;
                    scr[21][pl]=1
					*/
			 case (77):case 'D':
				if(pl<width-2)
					scr[21][pl]=0,scr[21][++pl]=1;
					break;
			 case (32):case 'W':/* w means fire */
				scr[20][pl]=2;
				break;
			 case 27 :/*"27"is "Esc"*/
			 	setting();
				break;
		}
	if(++j%density==0)//density means �ܶ�,Original value:j=0;density=30,30 times per cycle,one plane come out
 	{
		j=0;
		srand(time(NULL));
		scr[0][rand()%width]=3;/*Generate true random number for 0 line ,enemy airplane's coordinates are random.*/
	}
	if(++i%speed==0)//���Ƶл��ƶ��ٶȣ�������ӵ��ƶ��ٶ�,original value :i=0,speed =3,
		movepla(scr);/*3 times per cycle,perform movepla()*/
	movebul(scr);
	print(scr);
	if(i==30000)
		i=0;//����i Խ��
}
}
void print(int a[][N])/*N=35*/
{
system("cls");/*Clear the screen*/
int i,j;
for(i=0;i<22;i++)
{
	a[i][width-1]=4;
	for(j=0;j<width;j++)
	{
		if(a[i][j]==0)printf(" ");
		if(a[i][j]==1)printf("\5");//����һ��ķ���
		if(a[i][j]==2)printf(".");//�ӵ�
		if(a[i][j]==3)printf("\3"); //����л�����
		if(a[i][j]==4)printf("|");
		if(i==0&&j==width-1)printf("�÷֣�%d",score);//���Ͻ���ʾ�÷�
		if(i==1&&j==width-1)printf("������%d",death);
		if(i==2&&j==width-1)printf("���ã�Esc");
		
	}
	printf("\n");
}
}
void movebul(int a[][N])/*�ӵ��ƶ�����*/
{int i,j;
for(i=0;i<22;i++)
{
	for(j=0;j<width;j++)
	{
		if(i==0&&a[i][j]==2)
			a[i][j]=0;
		if(a[i][j]==2)
		{
			if(a[i-1][j]==3)
				score+=10,printf("\7");
			a[i][j]=0,a[i-1][j]=2;
		}
	}
}
}
void movepla(int a[][N])
{
int i,j;
for(i=21;i>=0;i--)//�����һ��������Ϊ�˱���ѵл�ֱ�ӳ�����顣
	for(j=0;j<width;j++)
	{
		if(i==21&&a[i][j]==3)a[i][j]=0;//���и�ֵ0 ����Խ�硣
		if(a[i][j]==3)a[i][j]=0,a[i+1][j]=3;
	}
if(a[20][pl]==3&&a[21][pl]==1)/*when meet the enemy plane ,death ++*/
	death++;
}
void setting(void)
{
int sw=0,i,j;
system("cls");
do
{
	sw=0;printf("\n ��Ϸ����Ĵ�С��1.��2.С>> ");
	switch(getche())
	{
		case '1':width=34;break;
		case '2':width=24;break;
		default:printf("\n ����������ѡ��...\n");
		sw=1;
	}
}
while(sw);
do
{
	sw=0;
	printf("\n ��ѡ��л��ܶȣ�1.��2.��3.С>> ");
	switch(getche())
	{
		case '0':density=10;break;
		case '1':density=20;break;
		case '2':density=30;break;
		case '3':density=40;break;
		default:printf("\n ����������ѡ��...\n");
		sw=1;
	}
}
while(sw);
do
{
	sw=0;
	printf("\n �л��ķ����ٶȣ�1.��2.��3.��>> ");
	switch(getche())
	{
		case '1':speed=2;
		break;
		case '2':speed=3;
		break;
		case '3':speed=4;
		break;
		default:printf("\n ����������ѡ��...\n");
		sw=1;
	}
}
while(sw);/*All pixels clear */
for(i=0;i<22;i++)
	for(j=0;j<45;j++)
		scr[i][j]=0;
scr[21][pl=9]=1;/*Set plane original position*/
printf("\n �����������...");
getch();
}
void menu(void)
{
printf("˵������A D  left right �����һ����ҷ��У�W space �����ӵ�\n ���ã��밴Esc\n ��ʼ��Ϸ�������\n");
if(getch()==27)
	setting();
}
