#include <stdio.h>

int sum = 0;
int arr[1000000];

int main(){

	int i;
	for (i=0;i<1000000;i++){
		arr[i] = i;
		sum = sum + arr[i];
	}

	printf("Sum of the array is %d",sum);
}
