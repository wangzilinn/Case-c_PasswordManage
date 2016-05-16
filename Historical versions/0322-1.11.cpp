#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
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
int dynamicellipsis(int t)
{
for(;t>0;t--)
{
	printf(".");
	Sleep(3);
}
printf("\n");
}
int  locatecursor(int x,int y)
{
if (x<0||y<0)
    return(0);
int x1=0,y1=0;
while(1)
{
	printf("\n");
	y1++;
	if (y1==y)
	    break ;
}
while(1)
{
	printf(" ");
	x1++;
	if (x1==x)
	    break ;
}
}
void beep(int i)
{
int count;
for(count=0;count<i;count++)
{
	printf("\a");
    Sleep(800);
}
}
int date()
{
int year,month,day,t;
time_t nowtime;
struct tm *timeinfo;
time(&nowtime);
timeinfo =localtime(&nowtime);
year=1900+timeinfo->tm_year;
month=1+timeinfo->tm_mon;
day=timeinfo->tm_mday;
t=year*10000+month*100+day;
return t;
}
void encryptordecryptforcharacterstring(char unencrypted[],char encrypted[],int i)
{
int key[]={2,1,1,1,6,9};
int n;/*Number of characters*/
int temp[61];/*Can encrypt less then 50 characters*/
int count;
int forloop;/*just for loop */
switch(i)/*1：encrypt 0：unencrypt*/
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
	case(1):*encrypted=((*unencrypted+96)*11-12)*2;break;
	case(0):*unencrypted=(((*encrypted/2)+12)/11)-96;break;
}
}
void mainmenu()
{
system("cls");
printf("				喵嗷~\n");
decoratline(1);/*-*/
printf("				FUNCTION:\n");
decoratline(7);/*center*/
printf("		1.Modify login password\n");
printf("		2.Modify login password error limit\n") ;
printf("		3.Password management system \n");
printf("		4.Function query system\n");
printf("		5.Game-Hit plane!\n");
printf("		6.Game-Snake\n");
printf("		7.Efficiency management system\n");
printf("		8.Task management system\n");
printf("		9.Countdown\n");
printf("		10.Timing shutdown\n");/*double Tab!!*/
printf("		  To be continued......\n");
printf("		0.Exit \n");
decoratline(1);
}
int login(char password[],char rpassword[],int k)/*judje "j" if 1 or 0*/
/* DONE (#1#): 密码加密！！ */
{
int i,j=0,count;
if(k>5)
    k=5;
for(i=0;i<k;)
{
	printf("Please enter the password：   %d chances left \n",k-i);
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
typedef struct logindata
{
	char loginpassword[21];
	int wrongnumber;
	int date;
}logindata;
typedef struct passworddatalink
{
	struct passworddata data1;
	struct passworddatalink *next;
}passworddatalink;
typedef struct sentence
{
	char s[10];
}sentence;
typedef struct numberdata
{
	int number;
	int order;
	int date;
	int pro;
}numberdata;
typedef struct numberdatalink
{
	numberdata score;
	struct numberdatalink *next;
}numberdatalink;
typedef struct functionQuery
{
	char name[20];
	char function[50];
	char codeExample[200];
	char codeResult[50];
	int pro;
}functionQuery;
typedef struct functionQueryLink
{
	functionQuery data;
	struct functionQueryLink *next;
}functionQueryLink;
int changethenumberofwrongtimes(int *n)
{
logindata justfornumber;
FILE *fp;
printf("The number of login password input is limit to %d time(s) \n",*n);
printf("To be modified as：  enter 0 to quit \n");
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
encryptordecryptfornumber(n,n,1);
fp=fopen("logindata","ab+");
fread(&justfornumber,sizeof(logindata),1,fp);
fclose(fp);
justfornumber.wrongnumber=*n;
fp=fopen("logindata","wb");
fwrite(&justfornumber,sizeof(logindata),1,fp);
fclose(fp);
printf("Modified successfully\n");
getch();
}
int changeloginpassword()
{
char old[21];
char new1[21],new2[21];
char validation[21];
logindata originalpassword;
FILE *fp;
int a,count;
fp=fopen("logindata","ab+");
fread(&originalpassword,sizeof(logindata),1,fp);
fclose(fp);
strcpy(old,originalpassword.loginpassword);
encryptordecryptforcharacterstring(old,old,0);
while(1)
{
	printf("Please enter the original password： enter 20*\"0\" to quit \n");
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
printf("original password：%s\n",old);
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
		printf("Please enter it again：\n");
		for (count=0;count<20;count++)
		{
			new2[count]=getch();
			printf("*");
		}
		new2[count]='\0';
		printf("\n");
		if(strcmp(new1,new2) == 0 )
		{
			fp=fopen("logindata","wb");
            encryptordecryptforcharacterstring(new1,new1,1);
			strcpy(originalpassword.loginpassword,new1);
			fwrite(&originalpassword,sizeof(logindata),1,fp);
			fclose(fp);
			printf("Password has been modified\n");
			getch();
			break; 
		}
		else
			printf("both the input passwords must be consistent,try again \n");
	}
 
}
void savenumberdatalink(numberdatalink *head)
{
FILE *fp;
numberdatalink *p;
int count=0,success=1;
fp=fopen("efficiency","wb");
if(fp==NULL)
{
	printf("Error occurred while saving the file\n");
	exit(1);
}
p=head->next;
while(p)
{
	if(fwrite(p,sizeof(numberdatalink),1,fp)==1)
	{
		p=p->next;
		count++;
	}
	else
		success=0;

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
		success=0;

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
int i;//菜单选择
passworddatalink *head,*p,*bp,*temp; /*head is link healer ,Link header is empty!! ，p是可移动的指针,bp in front of p*/
int judje ;//查找信息-》链表修改-》是否修改的判断 
int edit=0;/*查找信息-》链表修改-》查找出的链表计数*/ 
int select=0;/*查找信息-》链表修改-》确认修改-》选择修改哪一个的变量*/
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
    	printf ("Failed to open the file\n");
    	getch();
    	return (0);
	}
	printf ("loading");
	dynamicellipsis(3);
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
				printf("Please input name：  enter 0 to quit \n");
				gets(quitornot);
				if(strcmp(quitornot,"0")==0)
				return(0);
				strcpy(newp->data1.name,quitornot);
				decoratline(8);
				printf("please input username：\n");
				gets(newp->data1.username);
				printf("please input password：\n");
				gets(newp->data1.password);
                encryptordecryptforcharacterstring(newp->data1.password,newp->data1.password,1);
				printf("please input note ：\n");
				gets(newp->data1.note);//above:Assign values to the list
				newp->next=NULL;//p作为最后一个，那么p的指向为null
				last=head;//开始让last遍历链表，首先将last定位到链表头 
				while(last->next)
					last=last->next;/*Traversing the linked list*/
				last->next=newp;
				savepassworddatalink(head);/*保存文件 */
			}
			break;
		case(2)://查找链表 
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
		case(3)://显示全部信息
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
int savefunctionQueryLink(functionQueryLink *head)
{
FILE *fp;
functionQueryLink *p;
int count=0,success=1;
fp=fopen("functionQueryData","wb");
if(fp==NULL)
{
	printf("Error occurred while saving the file\n");
	exit(1);
}
p=head->next;
while(p)/*turn pro to 0*/
{
	p->data.pro=0;
	p=p->next;
}
p=head->next;/*reset p*/
while(p)
{
	if(fwrite(p,sizeof(functionQueryLink),1,fp)==1)
	{
		p=p->next;
		count++;
	}
	else
		success=0;

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
int functionquerysystem()
{
int i;//菜单选择
functionQueryLink *head,*p,*bp,*temp; /*head is link healer ,Link header is empty!! ，p是可移动的指针,bp in front of p*/
int judje ;//查找信息-》链表修改-》是否修改的判断
int edit=0;/*查找信息-》链表修改-》查找出的链表计数*/
int select=0;/*查找信息-》链表修改-》确认修改-》选择修改哪一个的变量*/
int count=0;/*just for count */
FILE *fp;
while(1)
{
	decoratline(2);/***/
	printf("			Function Query System \n");
	decoratline(7);/*center*/
	printf("		1:add function \n");
	printf("		2:find function \n");
	printf("		3:Display all functions\n");
	printf("		0:quit \n");
	decoratline(2);
	scanf("%d",&i);
	getchar();
	if(i==0)
	return(0);
	head=(functionQueryLink*)malloc(sizeof(functionQueryLink));/*create the head of the link list */
	head->next=NULL;
	p=head;/*move p to the head of the link list */
    fp=fopen("functionQueryData","ab+");/*open the file*/
    if (fp==NULL)
    {
    	printf ("Failed to open the file\n");
    	getch();
    	return (0);
	}
	printf ("loading");
	dynamicellipsis(3);
    while (!feof(fp))
    {
        temp =(functionQueryLink*)malloc(sizeof(functionQueryLink));
        if(fread(temp,sizeof(functionQueryLink),1,fp)==1)
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
			functionQueryLink *last;
			char quitornot[30];/*"name"'s characters are limited to 30*/
			while(1)
			{
				functionQueryLink *newp=(functionQueryLink*)malloc(sizeof(functionQueryLink));
				printf("Please input function name：  enter 0 to quit \n");
				gets(quitornot);
				if(strcmp(quitornot,"0")==0)
				return(0);
				strcpy(newp->data.name,quitornot);
				decoratline(8);
				printf("please input explain：\n");
				gets(newp->data.function);
				printf("please input example：\n");
				gets(newp->data.codeExample);
				printf("please input result ：\n");
				gets(newp->data.codeResult);//above:Assign values to the list
				newp->next=NULL;//p作为最后一个，那么p的指向为null
				last=head;//开始让last遍历链表，首先将last定位到链表头
				while(last->next)
					last=last->next;/*Traversing the linked list*/
				last->next=newp;
				savefunctionQueryLink(head);/*保存文件 */
			}
			break;
		case(2)://查找链表
			char name[20];
			if(head ==NULL )
				printf ("the data is empty \n");
			else
			{
				printf ("Enter the function name or explanation you want to find:\n");
				gets (name);
				p=head->next;
				edit=1;
				while(p)
				{
					if((strstr(p->data.name,name)||p->data.function)!=NULL) /*if name is contained in p->data1.name*/
					{
                        decoratline(8);
						printf("%d->function name:",edit);
						puts(p->data.name);
						decoratline(8);
						printf("explanation:");
						puts (p->data.function);
						printf("example:\n");
                        printf(">>>");
						puts (p->data.codeExample);
						printf("\nresult:");
						puts (p->data.codeResult);
						printf ("\n");
						p->data.pro=edit ;
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
						if(p->data.pro==select )
						{
                            decoratline(8);
							printf("%s\n",p->data.name);
							decoratline(8);
							printf ("rename:\n");
							gets(p->data.name);
							printf("reinterpretation:\n");
							gets(p->data.function);
							printf ("example:\n>>>");
							gets (p->data.codeExample);
							printf ("result:\n");
							gets (p->data.codeResult);
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
                    	printf ("DEBUG -pro value- %d\n",p->data.pro);
                    	p=p->next;
					}
				 	#endif
					savefunctionQueryLink(head);
				}
				else if(judje == 2)/*delete the link */
				{
					select=0;
					printf ("Which one to delete?\n") ;
					scanf ("%d",&select);
					p=head->next;
                    while (p)
					{
						if(p->data.pro==select )
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
					savefunctionQueryLink(head);
				}/*when edit == 0 quit the cycle */
			}
			break;
		case(3)://显示全部信息
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
				puts(p->data.name);
				decoratline(8);
				printf("explain:");
				puts(p->data.function);
				printf("example:/n>>>");
				puts (p->data.codeExample);
				printf("result:");
				puts (p->data.codeResult);
				printf ("\n");
				p=p->next;
			}
			break;
		case(0):return(0);
	}
}
return(0);
}
int timingshutdown()
{
int judge,judget;
int i,ifshutdown=0;
char t[5];
char shutdown[20]="shutdown -s -t ";
char quitshutdown[20]="shutdown -a";
printf("set or cancel timing shutdown,enter 1 to set ,enter 2 to cancel \n");
scanf("%d",&i);
switch(i)
{
	case(1):
		printf("Please set time:      \nenter negative number to quit.\n ");
		scanf("%s",t);
		judget=atoi(t);
		if(judget<0)
		    return(0);
		system(strcat(shutdown,t));
		ifshutdown=1;
		/*fp=fopen........*/
		printf("\nThe function has been performed\n");
		getch();
		break ;
    case(2):
		#ifdef DEBUG
		ifshutdown=1;/*use fseek function to save "ifshutdown"*/
		#endif
		if(ifshutdown==0)
    	{
			printf("You haven't set the timing shutdown\n");
			return(0);
		}
		else
		{
			printf("Are you sure you want to cancel the timing shutdown ? \nenter 1 to confirm ,2 to quit \n");
            while(1)
			{

				scanf("%d",&judge);
				if(judge==1)
				{
	                system(quitshutdown);
	                printf("The function has been performed\n");
	                getch();
	                break;
				}
				else if(judge==2)
	                return(0);
	            else
	                printf("please input again\n");
			}
		}
}
}
int gamehitplane()
{
int scr[22][35]={0},pl=9,width=24,speed=3,density=30,score=0,death=0;
/*全局变量：界面、我机初始位、界面宽度、敌机速度、敌机密度、得分、死亡*/
int i,j;/*coordinate*/
int sw=0;
int fps1=0,fps2=0;
printf("key operational control on the direction of the game,the space bar launch a missile.\n");
printf("press ESC key to enter setup,press any key to start the game ");
system("cls");/*clear screen */
do
{
	sw=0;printf("\nThe size of the game interface：1.big 2.small >> ");
	switch(getche())
	{
		case '1':width=34;break;
		case '2':width=24;break;/*out of switch*/
		default:printf("\n Please try again \n");
		sw=1;
	}
}
while(sw);
do
{
	sw=0;
	printf("\n Please select the difficulty of the game:0.very hard 1.hard 2.normal 3.easy\n");
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
	if(kbhit())/*Check whether the button is pressed,if pressed return 1，else return 0,press any key to enter the game */
		switch(getch())//控制左右移动和进入菜单
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
	if(++fps1%density==0)//density means 密度,Original value:j=0;density=30,30 times per cycle,one plane come out
 	{
        fps1=0;
		srand(time(NULL));
		scr[0][rand()%width]=3;/*Generate true random number for 0 line ,enemy airplane's coordinates are random.*/
	}
	if(++fps2%speed==0)//控制敌机移动速度，相对于子弹移动速度,original value :i=0,speed =3,
	{
		i=0;j=0;
		for(i=21;i>=0;i--)//从最后一行往上是为了避免把敌机直接冲出数组。
		for(j=0;j<width;j++)
		{
			if(i==21&&scr[i][j]==3)scr[i][j]=0;//底行赋值0 以免越界。
			if(scr[i][j]==3)scr[i][j]=0,scr[i+1][j]=3;
		}
		if(scr[20][pl]==3&&scr[21][pl]==1)/*when meet the enemy plane ,death ++*/
			death++;
	}
if(fps2==30000)
	fps2=0;//以免fps越界
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
			if(scr[i][j]==1)printf("\5");//输出我机的符号
			if(scr[i][j]==2)printf(".");//子弹
			if(scr[i][j]==3)printf("\3"); //输出敌机符号
			if(scr[i][j]==4)printf("|");
			if(i==0&&j==width-1)printf("score：%d",score);//右上角显示得分
			if(i==1&&j==width-1)printf("death：%d",death);
  			if(i==2&&j==width-1)printf("enter Esc to quit ");

		}
		printf("\n");
	}
}
}
int gamesnake()
{

}
/* TODO (#1#): efficiency management !!!! */
int efficiencymanagementsystem()/*link!!!!*/
{
int select;
int newscore;
int judge=0;
sentence week[7];
int count=0;
numberdatalink *p,*head,*last,*temp,*newp;
FILE *fp;
strcpy(week[0].s,"Monday");
strcpy(week[1].s,"Tuesday");
strcpy(week[2].s,"Wednesday");
strcpy(week[3].s,"Thursday");
strcpy(week[4].s,"Friday");
strcpy(week[5].s,"Saturday");
strcpy(week[6].s,"Sunday");
while(1)
{
	fp=fopen("efficiency","ab+");
	if(fp==NULL)
	{
		printf("Failed to open the file\n");
		getch();
		return(0);
	}
	printf("\nloading");
	dynamicellipsis(3);
	head=(numberdatalink*)malloc(sizeof(numberdatalink));
	head->next=NULL;
	p=head;
	while(!feof(fp))
	{
		temp=(numberdatalink*)malloc(sizeof(numberdatalink));
		if(fread(temp,sizeof(numberdatalink),1,fp)==1)
		{
			temp->next=NULL;
			p->next=temp;
			p=temp;
			count++;
		}
	}
	fclose(fp);
	printf ("The file is already open,importing %d records\n",count);
	decoratline(2);
	printf("			Efficiency Management System\n");
	decoratline(7);/*while ,but if function 1 has been run ,then just function 2 is permit*/
	last=head;/*locate last*/
	while(last->next)
	    last=last->next;
    if(last->score.date==date())
        judge=1;/*today's data has been changed */
	if(judge==0)
		printf("enter 1 to set today's score,enter 2 to display all scores，enter 3 to quit.\n");
	else
	    printf("enter 1 to display all scores ,enter 2 to quit.\n");
	while(1)
	{
		scanf("%d",&select);
		if(select==1||select==2||select==3)
		{
			if(judge==0)
				break;
	        else if(judge==1&&(select==1||select==2))
			{
				select++;/*relocat select to 2*/
				break;
			}
	        else
				printf("You entered a wrong number,please try again.\n");
		}
		else
		    printf("You entered a wrong number,please try again.\n");
	}
	switch(select)
	{
		case(1):/*today's score */
			printf("Today's score is ");
			scanf("%d",&newscore);
	        newp=(numberdatalink*)malloc(sizeof(numberdatalink));
	        newp->score.number=newscore;
	        newp->score.date=date();
	    	newp->next=NULL;
	    	last=head;//开始让last遍历链表，首先将last定位到链表头
			while(last->next)
				last=last->next;/*Traversing the linked list*/
			last->next=newp;
	        savenumberdatalink(head);
		    break;
	    case(2):/*display all scores*/
            printf("   %s",week[0].s);printf("   %s",week[1].s);printf("   %s",week[2].s);
 			printf("   %s",week[3].s);printf("   %s",week[4].s);printf("   %s",week[5].s);
			printf("   %s",week[6].s);
			count=0;/*reset count */
			p=head->next;
			while(p)
			{
				if(count%7==0)
				{
					printf("\n  ");
				}
				printf("     %d",p->score.number);
				p=p->next;
                count++;
			}
			getch();
			break;
		case(3):return(0);break;
	}
}
}
int taskmanagementsystem()
{
/* TODO (#1#): a.	录入界面包含时间，地点，事件
               b.	自动排序事件
               c.	把前一天没有完成的时转移到下
               一天 */

}
int countdown()
{
int min,vmin,sec,vsec,hour,vhour;
int t;
int count,temp;
time_t start, end;
decoratline(2);
printf("				Count down\n");
decoratline(7);
printf("Set the countdown time:\n");
printf("Hour:");
scanf("%d",&hour);
printf("Minute:");
scanf("%d",&min);
printf("Second:");
scanf("%d",&sec);
t=hour*3600+min*60+sec;
temp=t;
vsec=sec;
vmin=min;
vhour=hour;
system("cls");
#ifdef DEBUG
printf("%d\n",t);
Sleep(1000);
#endif
start = time(NULL);
end = time(NULL);
for(count=0;count<t;count++)
{
	while(end-start<count)
	{
		end=time(NULL);
	}
	system("cls");
	/*t-count is rest time*/
    printf("Hour:");
    for(temp=0;temp<hour;temp++)
        printf(".");
    printf("\nMinute:");
    for(temp=0;temp<min;temp++)
        printf(".");
    printf("\nSecond:");
    for(temp=0;temp<sec;temp++)
        printf(".");
    if(sec==0&&vmin!=0)
    {
    	min--;
    	sec=60;
	}
	if(min==0&&vhour!=0)
	{
		hour--;
		min=60;
	}
	sec--;
}
beep(6);
}
int main()
{
system("title 喵嗷！！");
logindata readfromfile;
char password[21];
/* DONE (#1#): 密码加密！！ */
char rpassword[21];//进入密码
int i;
/* DONE (#1#): when n is unlegal ,turn n =1
               limit n to 0~10; */
int n;//登陆时密码的输入限制 
FILE *fp;
fp=fopen("logindata","ab+");//读入初始密码
fread(&readfromfile,sizeof(logindata),1,fp);
fclose(fp);
n=readfromfile.wrongnumber;
encryptordecryptfornumber(&n,&n,0);
strcpy(rpassword,readfromfile.loginpassword);
encryptordecryptforcharacterstring(rpassword,rpassword,0);
i=login(password,rpassword,n);
switch (i)
{
	case(1):break;
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
			getch();//输入任意字符
	        exit(0);//退出程序。再次加入拓展发送邮件功能 
			break;
}
while(1)//当功能函数跳出时，循环出现菜单 
{
    mainmenu();
    printf("\n");
	scanf("%d",&i);
	getchar();//在两个scanf之间用getchar，去除缓存中的回车 
	switch(i)
	{
		case(1):changeloginpassword();break;
		case(2):changethenumberofwrongtimes(&n);break;
		case(3):passwordmanagementsystem();break;
		case(4):functionquerysystem();break;
		case(5):gamehitplane();break;
		case(6):gamesnake();break;
		case(7):efficiencymanagementsystem();break;
        case(8):taskmanagementsystem;break;
		case(9):countdown();break;
		case(10):timingshutdown();break;
		case(0):exit(0); 
	}
}
}

