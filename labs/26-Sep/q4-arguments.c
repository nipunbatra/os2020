// Example courtesy geeks4geeks

#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>

// size of array 
#define MAX 16 

// maximum number of threads 
#define MAX_THREAD 16


int a[MAX];

long long sum[MAX_THREAD] = { 0 }; 
int part = 0; 

void* sum_array(void* arg) 
{ 

	// Each thread computes sum of 1/MAX_Threadth of array 
	int thread_part = arg; 

	for (int i = thread_part * (MAX / MAX_THREAD); i < (thread_part + 1) * (MAX / MAX_THREAD); i++) 
		sum[thread_part] += a[i]; 
} 

// Driver Code 
int main() 
{ 
    for (int i=0;i<MAX;i++) a[i] = rand();

	pthread_t threads[MAX_THREAD]; 

	// Creating 4 threads 
	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_create(&threads[i], NULL, sum_array, (void*)i); 

	// joining 4 threads i.e. waiting for all 4 threads to complete 
	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_join(threads[i], NULL); 

	// adding sum of all 4 parts 
	long long total_sum = 0; 
	for (int i = 0; i < MAX_THREAD; i++) 
		total_sum += sum[i]; 

	printf("sum is: %lld\n", total_sum); 

	return 0; 
} 



