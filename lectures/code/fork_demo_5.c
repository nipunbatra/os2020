#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
printf("Current process ID is: %d\n", (int)getpid());
int rc = fork();
if (rc <0)
    {
    printf("Fork failed");
    }
else if (rc ==0)
    {
    // Child Process
    printf("Child: Current process ID is: %d\n", (int)getpid());
    sleep(50);
    }
else
   {
   printf("Parent of %d is %d\n", rc, (int) getpid());
   sleep(50);
   }
}


