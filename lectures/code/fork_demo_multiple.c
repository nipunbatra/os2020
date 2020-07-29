#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
printf("Current process ID is: %d\n", (int)getpid());
int rc_1 = fork();
int rc_2 = fork();
}


