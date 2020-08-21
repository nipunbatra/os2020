// CPP Program to find sum of array
#include <stdio.h>
#include <pthread.h>
#include <time.h>

// size of array
#define MAX 40000000000
#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)



int a[MAX];

long long sum[8] = { 0 };
int part = 0;

void* sum_array(void* arg)
{

    // Each thread computes sum of 1/4th of array
    int thread_part = part++;

    for (int i = thread_part * (MAX / 8); i < (thread_part + 1) * (MAX / 8); i++)
        {sum[thread_part] += a[i];}
}

// Driver Code
int main(int argc, char *argv[])
{
    char *p;
    int MAX_THREAD = (int) strtol( argv[1],&p, 10);
    for (long long  i=0; i<MAX; i++) a[i] = 0;

    TICK(A);
    pthread_t threads[MAX_THREAD];

    // Creating 4 threads
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_create(&threads[i], NULL, sum_array, (void*)NULL);

    // joining 4 threads i.e. waiting for all 4 threads to complete
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);

    // adding sum of all 4 parts
    int total_sum = 0;
    for (int i = 0; i < MAX_THREAD; i++)
        total_sum += sum[i];

    printf("sum is %l\n",total_sum);
    TOCK(A);
    return 0;
}
