#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <math.h>

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
	for(beg;beg<end;beg++){
		sum = sum + arr[beg];

	}

}

int main(){

	int n_thread,rc,i,n_elem,last;
	pthread_t t[100];
	struct arguments *(arg[100]);
	
	printf("Main Begin\n");
	printf("No. of threads to be launched?\n");
	scanf("%d",&n_thread);

	for(i=0;i<1000000;i++){
		arr[i] = i;
	}

	n_elem = (int)ceil((double)1000000/(double)n_thread);

	last = 0;

	for(i=0;i<n_thread;i++){
		arg[i] = (struct arguments *)malloc(sizeof(struct arguments));
		arg[i]->start = last;
		if (i == n_thread)
			arg[i]->stop = 1000000;
		else
			arg[i]->stop = last + n_elem;
		last = last + n_elem;
		rc = pthread_create(&t[i],NULL,sum_thread,arg[i]);
		assert(rc==0);
	}

	for(i=0;i<n_thread;i++){
		pthread_join(t[i],NULL);
	}	

	printf("Sum of the elements in the array is %d",sum);
	return 1;
}
