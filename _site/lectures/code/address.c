#include<stdio.h>
#include<stdlib.h>
int z = 10;
int main()
{

int x = 10;
int* y = malloc(4);
printf("Static: %p\nStack: %p\nHeap:%p\nCode: %p", &z, &x, y, main);
} 
