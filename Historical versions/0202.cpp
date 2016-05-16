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
passwordcontroladd()
{
}
passwordcontrolfind()
{
}
passwordcontrolall()
{
}
passwordcontrolmenu()//密码管理系统 
{int i;
printf("				密码管理\n"); 
printf("--------------------------------------------------------------------------------");
printf("1:增加密码\n");
printf("2:查找密码\n");
printf("3:显示全部密码\n");
printf("--------------------------------------------------------------------------------");
scanf("%d",&i);
switch(i)
	{case(1):passwordcontroladd();break;
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
switch(i)
{case(1):changeloginpassword();break;
 case(2):changethenumberofwrongtimes(&n);break;
 case(3):passwordcontrolmenu();break; 
 case(0):exit(0); 
 }
}
}

