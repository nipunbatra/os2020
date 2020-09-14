#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

//    Compile using gcc -std=c11 -pthread -o 2_atomic.out 2_atomic.c
_Atomic volatile long long int count = 0;


void* worker(void* arg) {
    for (int i =0;i<100000000; i++)
    {
    count++; 
    }
   
}

int main(int argc, char *argv[]) {
    pthread_t p, q;
    pthread_create(&p, NULL, worker, NULL);
    pthread_create(&q, NULL, worker, NULL);
    pthread_join(p, NULL);
    pthread_join(q, NULL);
    printf("Count is: %lld\n", count);
    return 0;
}
