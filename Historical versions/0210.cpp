#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
login(char password[],char rpassword[],int k)/*judje "j" is 1 or 0*/
{
int i,j=0;
for(i=0;i<k;)
{
	printf("���������룺   �㻹��%d�λ���\n",k-i);
	gets(password);
	if(strcmp(password,rpassword) == 0)
	{
		printf("��½�ɹ�\n"); 
		j=1;
		break;
	}
	else
	{
		printf("�������\n");
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
	int pro; 
};
typedef struct passworddatalink//���� 
{
	struct passworddata data1;
	struct passworddatalink *next;
}passworddatalink,*link1;

 
changethenumberofwrongtimes(int *n)
{
printf("Ŀǰ��¼������������������Ϊ%d��\n",*n);
printf("Ҫ�޸�Ϊ��  0Ϊȡ��");
scanf("%d",n);
if(*n==0) 
	return(0);
FILE *fp;
fp=fopen("wrongnumber","w");
fprintf(fp,"%d",*n);
fclose(fp);
printf("���ƴ����޸ĳɹ�\n"); 
}
changeloginpassword()
{
char old[20];
char new1[20],new2[20];
char validation[20];
FILE *fp;
int a;
fp=fopen("login","r");
fgets(old,21,fp);
fclose(fp);
for(;;)
{
	printf("������ԭ���룺 0Ϊȡ��\n"); 
	gets(validation);
	if(strcmp(validation,"0")==0)
		return(0); 
	if(strcmp(old,validation)!=0)
		printf("��ԭ���벻ƥ��\n"); 
	else
		break; 
	}
printf("ԭ����Ϊ��%s\n",old);
while(1)
	{
		printf("�����������룺\n");
		gets(new1);
		printf("������һ�飺\n"); 
		gets(new2);
		if(strcmp(new1,new2) == 0 )
		{
			fp=fopen("login","w");
			fputs(new1,fp);
			fclose(fp);
			printf("�����޸ĳɹ�\n");
			break; 
		}
		else
			printf("�������벻һ�£�����������"); 
	}
 
}

passwordcontrolmenu()//�������ϵͳ 
{int i;//�˵�ѡ��
passworddatalink *head,*p; /*head������ͷ��p�ǿ��ƶ���ָ��*/ 
int judje ;//������Ϣ-�������޸�-���Ƿ��޸ĵ��ж� 
int edit=0;/*������Ϣ-�������޸�-�����ҳ����������*/ 
int select=0;/*������Ϣ-�������޸�-��ȷ���޸�-��ѡ���޸���һ���ı���*/ 
while(1)
	{printf("				�������\n"); 
	printf("--------------------------------------------------------------------------------");
	printf("1:��������\n");
	printf("2:��������\n");
	printf("3:��ʾȫ������\n");
	printf("0:�˳�\n");
	printf("--------------------------------------------------------------------------------");
	scanf("%d",&i);
	getchar();
	if(i==0)
	return(0);
    /*���ļ���ȡ������*/
	switch(i)
		{case(1):/*��������*/
			passworddatalink *last;
			char quitornot[30];//name���ַ�����Ϊ30 
			while(1)
			{passworddatalink *p=(passworddatalink*)malloc(sizeof(passworddatalink)); 
			printf("�����û�����  0Ϊȡ��/n"); 
			gets(quitornot);
			getchar();
			if(strcmp(quitornot,"0")==0) 
			return(0);
			strcpy(p->data1.name,quitornot);
			printf("�������룺/n");
			gets(p->data1.password);
			getchar(); 
			printf("���뱸ע��/n");
			gets(p->data1.note);//Ϊ������µ�һ���֣���p��ֵ��
			p->next=NULL;//p��Ϊ���һ������ôp��ָ��Ϊnull
			last=head;//��ʼ��last�����������Ƚ�last��λ������ͷ 
			if(last){//����������һ�� last=head ����headΪ�ǿգ�������һ��������ʹ����ʼif������������
				while(last->next) 
				last=last->next;
				last->next=p; 
				}
			else//����ǿ��������p��Ϊ����ͷ 
				head=p;
			}
			//�����ļ�
			break; 
		case(2)://�������� 
			char name[30]; 
			
			if(head ==NULL )
				printf ("����Ϊ��");
			else 
			{
				printf ("�����û���");
				gets (name);
				p=head;
				edit=0; 
				while(p)
				{
					if(strstr(p->data1.name,name)!=NULL) 
					{
						printf("%d.",edit); 
						puts(p->data1.name);
						printf ("\n");
						puts (p->data1.password);
						printf ("\n");
						puts (p->data1.note);
						printf ("\n");
						p->data1.pro=edit ;
						edit ++; 
						p=p->next;
					}
					else 
					{
						p=p->next;			
				 	} 
				} 
				printf ("��ѯ���,�Ƿ�Ҫ�޸ģ� 1 Yes 0 No");
				scanf("%d",&judje) ;
				if(judje)
				{
					select=0; 
					printf ("�޸���һ����") ;
					scanf ("%d",&select) ;
					p=head ;
					while (p) 
					{
						if(p->data1.pro==select ) 
						{
							printf ("�û���:/n") ;
							gets(p->data1.name);
							getchar();  
							printf("password:/n");
							gets(p->data1.password);
							getchar(); 
							printf ("note:/n");
							gets (p->data1.note);
							getchar();
						}
						else 
						{
							p=p->next; 
						} 
				 	}
				 	printf ("change complete,saving.....");
				 	p=head;
					while (p)/*��pro�е�������*/
					{
						p->data1.pro=0;
						p->next; 
					}
					/*save link*/
					printf ("save is complete ") ;
					
				}
			} 
			break;
		case(3)://��ʾȫ����Ϣ
			if(head ==NULL)
			{
				printf ("����Ϊ��");
				getchar(); 
			}
			else
				p=head; 
			while(p)
			{
				puts(p->data1.name);
				printf ("\n");
				puts (p->data1.password);
				printf ("\n");
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

main()
{
char password[20];
char rpassword[20];//�������� ,��ʼ���� Ϊ123 
int i;
int n;//��½ʱ������������� 
FILE *fp;
fp=fopen("wrongnumber","r");
fscanf(fp,"%d",&n);
fclose(fp);
fp=fopen("login","r");//�����ʼ���� 
fgets(rpassword,21,fp);
fclose(fp);
i=login(password,rpassword,n);
switch (i)
{
	case(1):printf("��~\n");break;
	case(0):getch();//���������ַ�
	        exit(0);//�˳������ٴμ�����չ�����ʼ����� 
			break;
}
while(1)//�����ܺ�������ʱ��ѭ�����ֲ˵� 
{
	printf("����\n");
	printf("1.�޸ĵ�¼����\n");
	printf("2.�޸���������������\n") ;
	printf("3.�������ϵͳ\n");
	printf("4.��������\n"); 
	printf("0.�˳�\n");
	scanf("%d",&i);
	getchar();//������scanf֮����getchar��ȥ�������еĻس� 
	switch(i)
	{
		case(1):changeloginpassword();break;
		case(2):changethenumberofwrongtimes(&n);break;
		case(3):passwordcontrolmenu();break; 
		case(0):exit(0); 
	}
}
}

