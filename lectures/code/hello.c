#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main ()
{
int x = 10;
printf("Hello there! x = %d\n", x);
printf("My pid is: %d", (int)(getpid()));
return 0;
}
