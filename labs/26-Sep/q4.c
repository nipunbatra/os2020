// Example courtesy geeks4geeks

#include <stdio.h> 
#include <pthread.h> 

// size of array 
#define MAX 16 

// maximum number of threads 
#define MAX_THREAD 1


int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 }; 
int sum[MAX_THREAD] = { 0 }; 
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

	pthread_t threads[MAX_THREAD]; 

	// Creating 4 threads 
	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_create(&threads[i], NULL, sum_array, (void*)i); 

	// joining 4 threads i.e. waiting for all 4 threads to complete 
	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_join(threads[i], NULL); 

	// adding sum of all 4 parts 
	int total_sum = 0; 
	for (int i = 0; i < MAX_THREAD; i++) 
		total_sum += sum[i]; 

	printf("sum is: %d\n", total_sum); 

	return 0; 
} 



