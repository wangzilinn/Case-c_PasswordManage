#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
login(char password[],char rpassword[],int k)
{
int i,j=0;
for(i=0;i<k;)
{printf("请输入密码：   你还有%d次机会\n",k-i);
gets(password);
if(strcmp(password,rpassword) == 0)
{printf("登陆成功\n"); 
j=1;
break;}
else
{printf("密码错误\n");
i++;
}
}
return j;
}
struct passworddata 
{
	char name[30];
	char password[20];
	char note[60];
};
typedef struct passworddatalink//链表 
{
	struct passworddata data1;
	struct passworddatalink *next;
}passworddatalink,*link1;

 
changethenumberofwrongtimes(int *n)
{printf("目前登录密码输入错误次数限制为%d次\n",*n);
printf("要修改为：  0为取消");
scanf("%d",n);
if(*n==0) 
	return(0);
FILE *fp;
fp=fopen("wrongnumber","w");
fprintf(fp,"%d",*n);
fclose(fp);
printf("限制次数修改成功\n"); 
}
changeloginpassword()
{char old[20];
char new1[20],new2[20];
char validation[20];
FILE *fp;
int a;
fp=fopen("login","r");
fgets(old,21,fp);
fclose(fp);
	for(;;)//输出有问题，找不到问题出在哪 
	{printf("请输入原密码： 0为取消\n"); 
	gets(validation);
	if(strcmp(validation,"0")==0)
		return(0); 
	if(strcmp(old,validation)!=0)
		printf("与原密码不匹配\n"); 
	else
		break; 
	}
printf("原密码为：%s\n",old);
while(1)
	{printf("请输入新密码：\n");
	gets(new1);
	printf("再输入一遍：\n"); 
	gets(new2);
	if(strcmp(new1,new2) == 0 )
		{fp=fopen("login","w");
		fputs(new1,fp);
		fclose(fp);
		printf("密码修改成功\n");
		break; 
		}
	else
		printf("两次密码不一致，请重新输入"); 
	}
 
}
passwordcontroladd(passworddatalink *head)
{passworddatalink *last;
char quitornot[30];//name的字符限制为30 
while(1)
{passworddatalink *p=(passworddatalink*)malloc(sizeof(passworddatalink)); //链表练习：先让p指向链表那么大的空间，错误：强制转换格式（passworddatalink*）中的*要注意 
	printf("输入用户名：  0为取消/n"); 
	gets(quitornot);
	getchar();
	if(strcmp(quitornot,"0")==0) 
	return(0);
	strcpy(p->data1.name,quitornot);
	printf("输入密码：/n");
	gets(p->data1.password);
	getchar(); 
	printf("输入备注：/n");
	gets(p->data1.note);//为链表的新的一部分（即p赋值）
p->next=NULL;//p作为最后一个，那么p的指向为null
last=head;//开始让last遍历链表，首先将last定位到链表头 
if(last){//由于有上面一句 last=head ，当head为非空，即不是一个空链表使，开始if函数遍历链表
	while(last->next) 
	last=last->next;
	last->next=p;
	}
else//如果是空链表，则把p作为链表头 
	head=p;
}
//保存到文件 !!!
 
}
passwordcontrolfind()
{
}
passwordcontrolall()
{
}
passwordcontrolmenu()//密码管理系统 
{int i;//菜单选择
link1 l;
passworddatalink *p,*r;
FILE *fp;
fp=fopen("passworddata","ab+");
 if(fp==NULL)
 {
  printf("\n=====>提示:文件不能打开!\n");
  exit(0);
 }

 
printf("				密码管理\n"); 
printf("--------------------------------------------------------------------------------");
printf("1:增加密码\n");
printf("2:查找密码\n");
printf("3:显示全部密码\n");
printf("--------------------------------------------------------------------------------");
scanf("%d",&i);
getchar();
switch(i)
	{case(1):passwordcontroladd(head);break;//改为含参函数，参数为链表头 
	 case(2):passwordcontrolfind();break;
	 case(3):passwordcontrolall();break;
	 case(0):return(0);
	}
}

main()
{char password[20];
char rpassword[20];//进入密码 ,初始密码 为123 
int i;
int n;//登陆时密码的输入限制 
FILE *fp;
fp=fopen("wrongnumber","r");
fscanf(fp,"%d",&n);
fclose(fp);
fp=fopen("login","r");//读入初始密码 
fgets(rpassword,21,fp);
fclose(fp);
i=login(password,rpassword,n);
switch (i)
{case(1):printf("喵~\n");break;
 case(0):getch();//输入任意字符
         exit(0);//退出程序。再次加入拓展发送邮件功能 
		 break;
}
while(1)//当功能函数跳出时，循环出现菜单 
{printf("功能\n");
printf("1.修改登录密码\n");
printf("2.修改密码错误次数限制\n") ;
printf("3.密码管理系统\n");
printf("4.待续……\n"); 
printf("0.退出\n");
scanf("%d",&i);
getchar();//在两个scanf之间用getchar，去除缓存中的回车 
switch(i)
{case(1):changeloginpassword();break;
 case(2):changethenumberofwrongtimes(&n);break;
 case(3):passwordcontrolmenu();break; 
 case(0):exit(0); 
 }
}
}

