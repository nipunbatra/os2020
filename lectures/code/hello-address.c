#include<stdio.h>
#include<stdlib.h>

int x = 100;

int main()
{
int y = 10;
int z = 20;
z = z*8;
int* a = malloc(4);
printf("Static: %p\nCode: %p\nStack: %p\nHeap: %p", &x, main, &y, a);
return y+z;
}
