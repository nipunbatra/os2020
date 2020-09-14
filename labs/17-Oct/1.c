#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

int sum = 0;
int arr[1000000];
struct arguments{
	int start;
	int stop;
	};

void *sum_thread(void *args){

	struct arguments *arg;
	arg = (struct arguments *)args;
	int beg,end;
	beg = arg->start;
	end = arg->stop;
	for (beg;beg<end;beg++){
		sum = sum + arr[beg];
	}

}

int main(){

	printf("Main begin\n");

	pthread_t t1,t2;
	int i,rc;
	struct arguments *arg1,*arg2;

	for (i=0;i<1000000;i++){
		arr[i] = i;
	}

	arg1 = (struct arguments *)malloc(sizeof(struct arguments));
	arg1->start = 0;
	arg1 -> stop = 500000;
	rc = pthread_create(&t1,NULL,sum_thread,arg1);
	assert(rc==0);

	arg2 = (struct arguments *)malloc(sizeof(struct arguments));
	arg2->start = 500000;
	arg2->stop = 1000000;
	rc = pthread_create(&t2,NULL,sum_thread,arg2);
	assert(rc==0);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	printf("Sum of array is %d\n",sum);
	return 1;


	

}
