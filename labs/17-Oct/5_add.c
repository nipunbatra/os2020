#include<stdio.h>

int main(){

	int x = 100;
	asm("incl %0": "+r"(x));
	asm("shll %0": "+r"(x));
	printf("Value of 2*(x+1) is %d\n",x);

}
