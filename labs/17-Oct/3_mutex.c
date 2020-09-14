#include <stdio.h>	
#include <pthread.h>
#include <assert.h>


volatile long long int count = 0;
pthread_mutex_t lock;

void* worker(void* arg) {
    for (int i =0;i<100000000; i++)
    {
    pthread_mutex_lock(&lock);
    count++; 
    pthread_mutex_unlock(&lock);

    }
   
}

int main(int argc, char *argv[]) {
	if(pthread_mutex_init(&lock,NULL) != 0){
		printf("Mutex initialization failed\n");
		return 1;
	}
    pthread_t p, q;
	int rc;
    pthread_create(&p, NULL, worker, NULL);
    pthread_create(&q, NULL, worker, NULL);
    rc = pthread_join(p, NULL);
	assert(rc==0);
    rc = pthread_join(q, NULL);
	assert(rc==0);
    printf("Count is: %lld\n", count);
    return 0;
}

