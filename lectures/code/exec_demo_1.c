#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
printf("Parent process PID:%d\n", (int)(getpid()));
char *cmd = "./hello.out";
execvp(cmd, NULL);
printf("I will not execute :( ----\n");
}


