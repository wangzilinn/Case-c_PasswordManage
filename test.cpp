#include<stdio.h>
#include<ctype.h>
#define DEBUG
int ChangeInToLowercase(char *input,char *output)
{
	int temp,count=0;
    while (input[count]!=NULL)//count original string
        count++;
    for(temp = 0;temp < count;temp ++)
        output[temp] = tolower(input[temp]);
	
}
main()
{
    char name[30];
    gets(name);
	ChangeInToLowercase(name,name);
	printf("%s",name);
}
