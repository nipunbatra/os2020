#include <stdio.h>	
#include <pthread.h>
#include <assert.h>

int counter;
int lock = 0;

char CompareAndSwap(int *ptr, int old, int new) {

unsigned char ret;
// Note that sete sets a ’byte’ not the word
__asm__ __volatile__ ("  lock\n"
"  cmpxchgl %2,%1\n"
"  sete %0\n"
: "=q" (ret), "=m" (ptr)
: "r" (new), "m" (*ptr), "a" (old)
: "memory");
return ret;
}


void *counter_thread(void *arg){

	int i = 0;

	printf("Thread %s begins\n",(char *)arg);

	while(i < 1000000){
		while(TestAndSet(lock,1)==1);
		counter = counter + 1;
		lock = 0;
		//printf("%s : %d\n",(char *)arg,counter);
		i = i + 1;
	}
	return NULL;
}

int main(){
	pthread_t t1,t2;
	int rc;
	
	printf("Main:begin\n");
	
	rc = pthread_create(&t1,NULL,counter_thread,"A");
	assert(rc==0);	

	rc = pthread_create(&t2,NULL,counter_thread,"B");
	assert(rc==0);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	printf("Main:End %d",counter);
	return 1;		
}
