#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

static volatile int counter = 0;

void *our_thread(void *arg){
	printf("Started %d\n", (int) arg);
	int i;
	for (i = 0; i < 1e2; i++) {
	counter = counter + 1;
	 }
	printf("%d: Counter: \n", counter);
	printf("%s: Done\n", (int) arg);
	return NULL;
	}

int main(int argc, char *argv[]) {
	pthread_t p[5];
	int rc;

	printf("main: begin (counter = %d)\n", counter);
        for(int i = 0; i<2; i++)
	rc = pthread_create(&p[i], NULL, our_thread, (void *)(i));
	
	for (int i = 0; i< 2;i++)
		{
		printf("Waiting for %d\n", i);
		rc = pthread_join(p[i], NULL);
		}

        printf("main: begin (counter = %d)\n", counter);
	return 0;
	}

