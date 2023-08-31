#include<stdio.h>
#include<unistd.h>

int main()
{

fork();
fork();
printf("process running %d \n",getpid());
return 0;
}
