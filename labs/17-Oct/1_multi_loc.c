#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/* Compile with gcc -o 1_multi_loc.out 1_multi_loc.c -pthread -lm*/
int sum=0;

struct arguments{
	int start,stop,A[1000000];
};

void *sum_thread(void *args){

	struct arguments *arg;
	arg = (struct arguments *)args;
	int beg,end,A[1000000];
	beg = arg->start;
	end = arg->stop;
	//A = arg->A;
	//memcpy(arg-);
	for(beg;beg<end;beg++){
		sum = sum + arg->A[beg];
	}
}

int main(){

	printf("Main begin\n");

	pthread_t t[100];
	int rc,i,last,arr[1000000],n_thread,n_elem;
	struct arguments *(arg[100]);

	for(i=0;i<1000000;i++){
		arr[i] = i;
	}

	printf("No of threads to be launched?\n");
	scanf("%d",&n_thread);
	

	n_elem = (int)ceil((double)1000000/(double)n_thread);
	
	last = 0;

	for(i=0;i<n_thread;i++){
		arg[i] = (struct arguments *)malloc(sizeof(struct arguments));
	
		arg[i]->start = last;
		if(i==n_thread)
			arg[i]->stop = 1000000;
		else
			arg[i]->stop = last+n_elem;
		last = last + n_elem;

		memcpy(arg[i]->A,arr,sizeof(arr));
		rc = pthread_create(&t[i],NULL,sum_thread,arg[i]);
		assert(rc==0);
	}

	for(i=0;i<n_thread;i++){
		pthread_join(t[i],NULL);
	}

	printf("Sum of the elements of the array is %d",sum);
	return 1;
}
