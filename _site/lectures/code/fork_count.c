#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
int x = 10;
printf("x = %d\n", x);
int rc = fork();
if (rc <0)
    {
    printf("Fork failed");
    }
else if (rc ==0)
    {
    x = x + 10;
    printf("x = %d\n", x);
    // Child Process
    printf("Child: Current process ID is: %d\n", (int)getpid());
    }
else
   {
    wait(NULL);
   printf("x = %d\n", x);
   }
}


