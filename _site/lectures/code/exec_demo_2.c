#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
char *cmd = "./hello2.out";
char *arg[3];
arg[0] = argv[0];
arg[1] = "1000";
arg[2] = NULL;
execvp(cmd, arg);
}


