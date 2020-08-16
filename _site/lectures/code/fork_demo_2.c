#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
printf("Parent of Current process has ID is: %d\n", (int)getppid());
}


