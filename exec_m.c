#include<stdio.h>
#include<unistd.h>

int main()
{

char *cmd_str = "/bin/ls";
char *argv[] = {cmd_str, "../foo", "/bar", NULL };

printf("process %d",getpid());

execv(cmd_str,argv);
return 0;
}
