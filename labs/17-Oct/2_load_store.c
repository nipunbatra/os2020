#include <stdio.h>
#include <pthread.h>

volatile long long int count = 0;
int lock = 0;

void* worker(void* arg) {
    for (int i =0;i<100000000; i++)
    {
    while(lock);
    lock=1;
    count++; 
    lock = 0; 

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
