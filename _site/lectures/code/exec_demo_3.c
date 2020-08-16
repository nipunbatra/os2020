#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
char *cmd = "./hello2.out";
char *arg[100];
int i=0;
for (i=0; i<argc;i++)
{
arg[i] = argv[i+1];
}
arg[i] = NULL;

execvp(cmd, arg);
}


