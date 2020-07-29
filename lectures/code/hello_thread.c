#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


void *our_thread(void *arg){
	printf("Started %d. My ID: %d\n", (int) arg, getpid());
	sleep(2);
	return NULL;
	}

int main(int argc, char *argv[]) {
	pthread_t p[26];
	int rc;
	printf("main: begin\n");
        for(int i = 0; i<26; i++)
	rc = pthread_create(&p[i], NULL, our_thread, (void *)(i));
	
	for (int i = 0; i< 26;i++)
		{
		printf("Waiting for %d\n", i);
		rc = pthread_join(p[i], NULL);
		}

        printf("main: end\n");
	return 0;
	}

