#include<stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int g_first,g_second,g_third;

void PrintVariable()
{
	int j,k,l;
	printf("address of variable j is %p\n",&j );
	printf("address of variable k is %p\n",&k );
	printf("address of variable l is %p\n",&l );	
	printf("address of variable g_first is %p\n",&g_first );
	printf("address of variable g_second is %p\n",&g_second );
	printf("address of variable g_third is %p\n",&g_third );

}

int main()
{

	int a,b,c;
	printf("address of variable a is %p\n",&a );
	printf("address of variable b is %p\n",&b );
	printf("address of variable c is %p\n",&c );
	printf("address of variable g_first is %p\n",&g_first );
	printf("address of variable g_second is %p\n",&g_second );
	printf("address of variable g_third is %p\n",&g_third );	

	pid_t ChildPID;
	ChildPID = fork();
	if(ChildPID  ==0)//child1
	{
		FILE * fp;
		fp= fopen("child1.sh","w+");
		fprintf(fp,"kill -9 %d\n",getpid());
		fclose(fp);
		printf("child1\n");
		PrintVariable();
		while(1)
		{

		}
	}
	else if (ChildPID > 0)//parent of child 1
	{
		ChildPID = fork();
		if(ChildPID  ==0)//child2
		{ 
			FILE * fp;
			fp= fopen("child2.sh","w+");
			fprintf(fp,"kill -9 %d\n",getpid());
			fclose(fp);
			printf("child2\n");
			PrintVariable();
			while(1)
			{

			}
		}
		else if(ChildPID > 0)//parent of child 1 and child 2 
		{
			ChildPID = fork();
			if(ChildPID  ==0)//child3
			{
				FILE * fp;
				fp= fopen("child3.sh","w+");
				fprintf(fp,"kill -9 %d\n",getpid());
				fclose(fp);
				printf("child3\n");
				PrintVariable();
				while(1)
				{

				}
			}
			else if(ChildPID > 0)//parent of child 1, child 2 and child 3 
			{
				FILE * fp;
				fp = fopen("parent.sh","w+");
				fprintf(fp,"kill -9 %d\n",getpid());
				fclose(fp);
				while(1)
				{

				}	
			}
			else //error creating child 3
			{

				printf("error ocurred creating child 3\n");
				exit(0);
			}
				
		}
		else //error creating child 2
		{
			printf("error ocurred creating child 2\n");
			exit(0);
		}
			
	}
	else //error creating child 1
	{

		printf("error ocurred creating child 3\n");
		exit(0);
	}

	return 0;
}