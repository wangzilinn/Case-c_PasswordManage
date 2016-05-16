#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
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
 	printf ("---------\n");

}
void mainmenu()
{
decoratline(1);/*-*/
printf("				FUNCTION:\n");
decoratline(7);/*center*/
printf("		1.Modify login password\n");
printf("		2.Modify login password error limit\n") ;
printf("		3.Password management system \n");
printf("        4.Function query system\n");
printf("		  To be continued......\n");
printf("		0.Exit \n");
decoratline(1);
}
int login(char password[],char rpassword[],int k)/*judje "j" if 1 or 0*/
/* TODO (#1#): 密码加密！！ */
{
int i,j=0,count;
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
typedef struct passworddatalink
{
	struct passworddata data1;
	struct passworddatalink *next;
}passworddatalink,*link1;

 
int changethenumberofwrongtimes(int *n)
{
printf("The number of login password input is limit to %d time(s) \n",*n);
printf("To be modified as：  enter 0 to quit \n");
scanf("%d",n);
if(*n==0) 
	return(0);
FILE *fp;
fp=fopen("wrongnumber","w");
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
			fp=fopen("login","wb");
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
                    if(edit!=1)
					{
						select=0;
						printf ("Which one to modify?\n");
						scanf ("%d",&select);
					}
					else
					{
						select=1;
					}
					getchar();
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
int main()
{
char password[21];
/* TODO (#1#): 密码加密！！ */
char rpassword[21];//进入密码
int i;
int n;//登陆时密码的输入限制 
FILE *fp;
fp=fopen("wrongnumber","r");
fscanf(fp,"%d",&n);
fclose(fp);
fp=fopen("login","ab+");//读入初始密码
fgets(rpassword,21,fp);
fclose(fp);
i=login(password,rpassword,n);
switch (i)
{
	case(1):printf("				喵嗷~\n");break;
	case(0):getch();//输入任意字符
	        exit(0);//退出程序。再次加入拓展发送邮件功能 
			break;
}
while(1)//当功能函数跳出时，循环出现菜单 
{
    mainmenu();
	scanf("%d",&i);
	getchar();//在两个scanf之间用getchar，去除缓存中的回车 
	switch(i)
	{
		case(1):changeloginpassword();break;
		case(2):changethenumberofwrongtimes(&n);break;
		case(3):passwordmanagementsystem();break;
		case(4):functionquerysystem();break;
		case(0):exit(0); 
	}
}
}

