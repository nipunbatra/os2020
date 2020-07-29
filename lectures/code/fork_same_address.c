#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>


int main()
{
int i = 2;
int ret = fork();
if (ret != 0) {
  //wait(NULL);
  printf("%p\n",(int*)&i); 
  i = 4;
  printf("%d\n", i);
  //sleep(10);
} else {
  printf("%p\n", (int*)&i);
  i = 3;
  printf("%d\n", i);
}
return 0;
}
