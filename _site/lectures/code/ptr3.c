#include<stdio.h>
#include<stdlib.h>

int main()
{
int *ptr;
int num=10;
ptr = (int *)malloc(num * sizeof(int));
for (int j=0;j<num;j++){
printf("%dth position of ptr is at:%p\n", j, ptr+j);
}
printf("Main is at: %p\n", main);
printf("Num is at: %p\n", &num);
return 0;
}
