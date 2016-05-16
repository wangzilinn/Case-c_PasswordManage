#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define DEBUG
void decoratline(int i)
{
if(i==1)
	printf ("--------------------------------------------------------------------------------");
else if (i==2)
	printf ("********************************************************************************");
else if (i==3)
	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
else if (i==4)
	printf ("................................................................................");
else if (i==5)
	printf ("################################################################################");
else if (i==6)
	printf ("================================================================================");
else if (i==7)/*center */
	printf ("                      ------------------------------\n");
else if (i==8)
	printf ("-------------\n");

}
void encryptordecryptforcharacterstring(char unencrypted[],char encrypted[],int i)
{
int key[]={2,1,1,1,6,9};
int n;/*Number of characters*/
int temp[61];/*Can encrypt less then 50 characters*/
int count;
int forloop;/*just for loop */
switch(i)/*1��encrypt 0��unencrypt*/
{
	case (1):
		n=0;
        while(unencrypted[n]!='\0')
            n++;
        for (count=0,forloop=1;count<n;count++,forloop++)
        {
			temp[count]=(int)(unencrypted[count]);
        	temp[count]=temp[count]-key[forloop%6];
        	encrypted[count]=(char)temp[count];
		}
		break ;
    case (0):
    	n=0;
		while(encrypted[n]!='\0')
		    n++;
        for (count=0,forloop=1;count<n;count++,forloop++)
		{
			temp[count]=(int)(encrypted[count]);
			temp[count]=temp[count]+key[forloop%6];
			unencrypted[count]=(char)temp[count];
    	}
		break ;
}

}
void encryptordecryptfornumber(int *unencrypted,int *encrypted,int i)
{
switch(i)
{
	case(1):*encrypted=((*unencrypted+96)*11-12)*2;
	case(2):*unencrypted=(((*encrypted/2)+12)/11)-96;
}
}
void mainmenu()
{
decoratline(1);/*-*/
printf("				FUNCTION:\n");
decoratline(7);/*center*/
printf("		1.Modify login password\n");
printf("		2.Modify login password error limit\n") ;
printf("		3.Password management system \n");
printf("		4.Function query system\n");
printf("		5.Hit plane!\n");
printf("		  To be continued......\n");
printf("		0.Exit \n");
decoratline(1);
}
int login(char password[],char rpassword[],int k)/*judje "j" if 1 or 0*/
/* DONE (#1#): ������ܣ��� */
{
int i,j=0,count;
if(k>5)
    k=5;
for(i=0;i<k;)
{
	printf("Please enter the password��   %d chances left \n",k-i);
	for (count=0;count<20;count++)
	{
		password[count]=getch();
		printf("*");
	}
    printf("\n");
	if(strcmp(password,rpassword) == 0)
	{
		printf("Login success\n");
		j=1;
		break;
	}
	else
	{
		printf("Password error\n");
		i++;
	}
}
return j;
}
struct passworddata 
{
	char name[30];
	char username[30];
	char password[20];
	char note[60];
	int pro; 
};
typedef struct passworddatalink
{
	struct passworddata data1;
	struct passworddatalink *next;
}passworddatalink,*link1;

 
int changethenumberofwrongtimes(int *n)
{
printf("The number of login password input is limit to %d time(s) \n",*n);
printf("To be modified as��  enter 0 to quit \n");
while(1)
{
	scanf("%d",n);
	if(*n<=5)
	    break ;
    else
    {
    	printf("the number of login password input must be less then 6 times\nplease set again \n");
	}
}
if(*n==0) 
	return(0);
FILE *fp;
fp=fopen("wrongnumber","w");
encryptordecryptfornumber(n,n,1);
fprintf(fp,"%d",*n);
fclose(fp);
printf("Modified successfully\n");
}
int changeloginpassword()
{
char old[21];
char new1[21],new2[21];
char validation[21];
FILE *fp;
int a,count;
fp=fopen("login","ab+");
fgets(old,21,fp);
fclose(fp);
encryptordecryptforcharacterstring(old,old,0);
while(1)
{
	printf("Please enter the original password�� enter 20*\"0\" to quit \n");
	for (count=0;count<20;count++)
	{
		validation[count]=getch();
		/* TODO (#1#): change password validation when it less then 
		               20 */
		printf("*");
	}
	validation[count]='\0';
	printf("\n");
	if(strcmp(validation,"00000000000000000000")==0)
		return(0); 
	if(strcmp(old,validation)!=0)
		printf("Does not match the original password\n");
	else
		break; 
	}
printf("original password��%s\n",old);
while(1)
	{
		printf("Please enter a new password\n");
		for (count=0;count<20;count++)
		{
			new1[count]=getch();
			printf("*");
		}
		new1[count]='\0';
		printf("\n");
		printf("Please enter it again��\n");
		for (count=0;count<20;count++)
		{
			new2[count]=getch();
			printf("*");
		}
		new2[count]='\0';
		printf("\n");
		if(strcmp(new1,new2) == 0 )
		{
			fp=fopen("login","wb");
            encryptordecryptforcharacterstring(new1,new1,1);
			fputs(new1,fp);
			fclose(fp);
			printf("Password has been modified\n");
			break; 
		}
		else
			printf("both the input passwords must be consistent,try again \n");
	}
 
}
void savepassworddatalink(passworddatalink *head)
{
FILE *fp;
passworddatalink *p;
int count=0,success=1;
fp=fopen("passworddata","wb");
if(fp==NULL)
{
	printf("Error occurred while saving the file\n");
	exit(1);
}
p=head->next;
while(p)/*turn pro to 0*/
{
	p->data1.pro=0;
	p=p->next;
}
p=head->next;/*reset p*/
while(p)
{
	if(fwrite(p,sizeof(passworddatalink),1,fp)==1)
	{
		p=p->next;
		count++;
	}
	else
	{
		success=0;
	}
}
if(success)
{
	printf("File saved successfully\n");
}
else
{
	printf("File write failed\n");
}
fclose(fp);
}
int passwordmanagementsystem()/*Password management system*/
{
int i;//�˵�ѡ��
passworddatalink *head,*p,*bp,*temp; /*head is link healer ,Link header is empty!! ��p�ǿ��ƶ���ָ��,bp in front of p*/
int judje ;//������Ϣ-�������޸�-���Ƿ��޸ĵ��ж� 
int edit=0;/*������Ϣ-�������޸�-�����ҳ�����������*/ 
int select=0;/*������Ϣ-�������޸�-��ȷ���޸�-��ѡ���޸���һ���ı���*/
int count=0;/*just for count */
FILE *fp;
while(1)
{
	decoratline(2);/***/
	printf("			Password Management System \n");
	decoratline(7);/*center*/
	printf("		1:add password \n");
	printf("		2:find password \n");
	printf("		3:Display all passwords\n");
	printf("		0:quit \n");
	decoratline(2);
	scanf("%d",&i);
	getchar();
	if(i==0)
	return(0);
	head=(passworddatalink*)malloc(sizeof(passworddatalink));/*create the head of the link list */
	head->next=NULL;
	p=head;/*move p to the head of the link list */
    fp=fopen("passworddata","ab+");/*open the file*/
    if (fp==NULL )
    {
    	printf ("File open failed\n");
    	return (0);
	}
	printf ("loading ....\n");
    while (!feof(fp))
    {
        temp =(passworddatalink*)malloc(sizeof(passworddatalink));
        if(fread(temp,sizeof(passworddatalink),1,fp)==1)
        {
        	temp->next=NULL;
        	p->next=temp;
        	p=temp;
        	count++;
		}
	}
	fclose(fp);
	printf ("The file is already open,importing %d records\n",count);
	count=0;/*when "count" already been used,take it back to 0 */
	switch(i)
	{
		case(1):/*add passworddata*/
			passworddatalink *last;
			char quitornot[30];/*"name"'s characters are limited to 30*/
			while(1)
			{
				passworddatalink *newp=(passworddatalink*)malloc(sizeof(passworddatalink));
				printf("Please input name��  enter 0 to quit \n");
				gets(quitornot);
				if(strcmp(quitornot,"0")==0)
				return(0);
				strcpy(newp->data1.name,quitornot);
				decoratline(8);
				printf("please input username��\n");
				gets(newp->data1.username);
				printf("please input password��\n");
				gets(newp->data1.password);
                encryptordecryptforcharacterstring(newp->data1.password,newp->data1.password,1);
				printf("please input note ��\n");
				gets(newp->data1.note);//above:Assign values to the list
				newp->next=NULL;//p��Ϊ���һ������ôp��ָ��Ϊnull
				last=head;//��ʼ��last�������������Ƚ�last��λ������ͷ 
				while(last->next)
					last=last->next;/*Traversing the linked list*/
				last->next=newp;
				savepassworddatalink(head);/*�����ļ� */
			}
			break;
		case(2)://�������� 
			char name[30]; 
			if(head ==NULL )
				printf ("the data is empty \n");
			else 
			{
				printf ("Enter the name you want to find:\n");
				gets (name);
				p=head->next;
				edit=1;
				while(p)
				{
					if(strstr(p->data1.name,name)!=NULL) /*if name is contained in p->data1.name*/
					{
                        decoratline(8);
						printf("%d->name:",edit);
						puts(p->data1.name);
						decoratline(8);
						printf("username:");
						puts (p->data1.username);
						printf("password:");
						encryptordecryptforcharacterstring(p->data1.password,p->data1.password,0);
						puts (p->data1.password);
						printf("note:");
						puts (p->data1.note);
						printf ("\n");
						p->data1.pro=edit ;
						edit++;
						p=p->next;
					}
					else 
					{
						p=p->next;			
				 	} 
				} 
				printf ("Query is completed,enter 1 to edit,2 to delete,enter 0 to quit \n");
				scanf("%d",&judje) ;
				getchar();
				if(judje==1)/*edit */
				{
                    if(edit!=2)
					{
						select=0;
						printf ("Which one to modify?\n");
						scanf ("%d",&select);
						getchar();
					}
					else
					{
						select=1;
					}
					p=head->next;
					while (p) 
					{
						if(p->data1.pro==select ) 
						{
                            decoratline(8);
							printf("%s\n",p->data1.name);
							decoratline(8);
							printf ("username:\n") ;
							gets(p->data1.username);
							printf("password:\n");
							gets(p->data1.password);
							encryptordecryptforcharacterstring(p->data1.password,p->data1.password,1);
							printf ("note:\n");
							gets (p->data1.note);
							break;
						}
						else 
						{
							p=p->next; 
						} 
				 	}
				 	printf ("change complete,saving.....\n");
				 	p=head->next;
				 	#ifdef DEBUG
                    while(p)
                    {
                    	printf ("DEBUG -pro value- %d\n",p->data1.pro);
                    	p=p->next;
					}
				 	#endif
					savepassworddatalink(head);
				}
				else if(judje == 2)/*delete the link */
				{
					select=0;
					printf ("Which one to delete?\n") ;
					scanf ("%d",&select) ;
					p=head->next;
                    while (p)
					{
						if(p->data1.pro==select )
						{
							bp=head;
							while (bp!=NULL )/*locate bp */
						    {
						    	if (bp->next==p)
						    	    break ;
                                bp=bp->next;
							}
                        	bp->next=p->next;
                            free (p);
                            break;/*bug here !*/
                      	}
						else
						{
							p=p->next;
						}
				 	}
				 	printf ("change complete,saving.....\n");
					savepassworddatalink(head);
				}/*when edit == 0 quit the cycle */
			}
			break;
		case(3)://��ʾȫ����Ϣ
			if(head==NULL)
			{
				printf ("password data is empty \n");
				getchar(); 
			}
			else
				p=head->next;
			while(p)
			{
                decoratline(8);
				printf("name:");
				puts(p->data1.name);
				decoratline(8);
				printf("username:");
				puts(p->data1.username);
				printf("password:");
				encryptordecryptforcharacterstring(p->data1.password,p->data1.password,0);
				puts (p->data1.password);
				printf("note:");
				puts (p->data1.note);
				printf ("\n");
				p=p->next;
			} 
			break;
		case(0):return(0);
	}
}
return(0);
}
int functionquerysystem()
{
/* TODO (#1#): input function name  ,output function 
               or
               input brief description,output detailed 
               description */

}
int gamehitplane()
{
int scr[22][35]={0},pl=9,width=24,speed=3,density=30,score=0,death=0;
/*ȫ�ֱ��������桢�һ���ʼλ��������ȡ��л��ٶȡ��л��ܶȡ��÷֡�����*/
int i,j;/*coordinate*/
int sw=0;
int fps1=0,fps2=0;
printf("key operational control on the direction of the game,the space bar launch a missile.\n");
printf("press ESC key to enter setup,press any key to start the game ");
system("cls");/*clear screen */
do
{
	sw=0;printf("\n ��Ϸ����Ĵ�С��1.��2.С>> ");
	switch(getche())
	{
		case '1':width=34;break;
		case '2':width=24;break;/*out of switch*/
		default:printf("\n ����������ѡ��...\n");
		sw=1;
	}
}
while(sw);
do
{
	sw=0;
	printf("\n Please select the difficulty of the game:0.very hard 1.hard 2.normal3.easy\n");
	switch(getche())
	{
		case '0':density=10;speed=2;break;
		case '1':density=20;speed=3;break;
		case '2':density=30;speed=4;break;
		case '3':density=40;speed=5;break;
		default:printf("\n data is illegal please try again \n");
		sw=1;
	}
}
while(sw);
#ifdef DEBUG
printf("\nThe last step is successful.");
#endif
for(i=0;i<22;i++)
	for(j=0;j<35;j++)
		scr[i][j]=0;
#ifdef DEBUG
printf("\nThe last step is successful.");
#endif
scr[21][pl=9]=1;/*Set plane original position*/
printf("\n press any key to save");
getch();
#ifdef DEBUG
printf("\nThe last step is successful.");
#endif
i=0;j=0;
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
             case (27):return(0);
                break;
		}
	if(++fps1%density==0)//density means �ܶ�,Original value:j=0;density=30,30 times per cycle,one plane come out
 	{
        fps1=0;
		srand(time(NULL));
		scr[0][rand()%width]=3;/*Generate true random number for 0 line ,enemy airplane's coordinates are random.*/
	}
	if(++fps2%speed==0)//���Ƶл��ƶ��ٶȣ�������ӵ��ƶ��ٶ�,original value :i=0,speed =3,
	{
		i=0;j=0;
		for(i=21;i>=0;i--)//�����һ��������Ϊ�˱���ѵл�ֱ�ӳ�����顣
		for(j=0;j<width;j++)
		{
			if(i==21&&scr[i][j]==3)scr[i][j]=0;//���и�ֵ0 ����Խ�硣
			if(scr[i][j]==3)scr[i][j]=0,scr[i+1][j]=3;
		}
		if(scr[20][pl]==3&&scr[21][pl]==1)/*when meet the enemy plane ,death ++*/
			death++;
	}
if(fps2==30000)
	fps2=0;//����fpsԽ��
	i=0;j=0;
	for(i=0;i<22;i++)/*bul*/
	{
		for(j=0;j<width;j++)
		{
			if(i==0&&scr[i][j]==2)
				scr[i][j]=0;
			if(scr[i][j]==2)
			{
				if(scr[i-1][j]==3)
					score+=10,printf("\7");
				scr[i][j]=0,scr[i-1][j]=2;
			}
		}
	}
	/*print */
	i=0;j=0;
	system("cls");/*Clear the screen*/
	for(i=0;i<22;i++)
	{
		scr[i][width-1]=4;
		for(j=0;j<width;j++)
		{
			if(scr[i][j]==0)printf(" ");
			if(scr[i][j]==1)printf("\5");//����һ��ķ���
			if(scr[i][j]==2)printf(".");//�ӵ�
			if(scr[i][j]==3)printf("\3"); //����л�����
			if(scr[i][j]==4)printf("|");
			if(i==0&&j==width-1)printf("�÷֣�%d",score);//���Ͻ���ʾ�÷�
			if(i==1&&j==width-1)printf("������%d",death);
			if(i==2&&j==width-1)printf("���ã�Esc");

		}
		printf("\n");
	}
}
}
int main()
{
char password[21];
/* DONE (#1#): ������ܣ��� */
char rpassword[21];//��������
int i;
/* DONE (#1#): when n is unlegal ,turn n =1
               limit n to 0~10; */
int n;//��½ʱ������������� 
FILE *fp;
fp=fopen("wrongnumber","r");
fscanf(fp,"%d",&n);
fclose(fp);
encryptordecryptfornumber(&n,&n,0);
fp=fopen("login","ab+");//�����ʼ����
fgets(rpassword,21,fp);
fclose(fp);
encryptordecryptforcharacterstring(rpassword,rpassword,0);
i=login(password,rpassword,n);
switch (i)
{
	case(1):printf("				���~\n");break;
	case(0):/*fp=fopen("wrongnumber","wb");
			fprintf(fp,"*&^&4W##$%^&*($%^&*())(*&^%^&*()(*&^%$%^&*()(*&^%$%^&*(*&^%$%^&*()%$(_)U",);
	        fclose(fp);
	        fp=fopen("login","wb");
	        fprintf(fp,"*&^&!@#$%^&*()_)(*&^%$#$%^&*()_)(*&^%$#@#$%^&*()_)(*&^%$#@!@#$%^&*()(*&^%$#$%^&*4W#%$(_)U",);
	        fclose(fp);
	        fp=fopen("passworddata","wb");
	        fprintf(fp,"*&^&4W@#$%^&*()_(*&^%$#$%^&*()_)(*&^%$#$%^&*())*&^%$#@$%^&*()*&^%$#%^&*()*&^%$^#%$(_)U",);
	        fclose(fp);*/
            decoratline(5);
			printf ("      All files have been emptied and filled with messy code\n");
	        printf("                    Do not try to break my program!\n");
			getch();//���������ַ�
	        exit(0);//�˳������ٴμ�����չ�����ʼ����� 
			break;
}
while(1)//�����ܺ�������ʱ��ѭ�����ֲ˵� 
{
    mainmenu();
	scanf("%d",&i);
	getchar();//������scanf֮����getchar��ȥ�������еĻس� 
	switch(i)
	{
		case(1):changeloginpassword();break;
		case(2):changethenumberofwrongtimes(&n);break;
		case(3):passwordmanagementsystem();break;
		case(4):functionquerysystem();break;
		case(5):gamehitplane();break;
		case(0):exit(0); 
	}
}
}
