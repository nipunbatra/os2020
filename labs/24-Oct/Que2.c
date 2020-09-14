#include <stdio.h>
#include <sys/time.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>


typedef struct __counter_t {
    int val;
    pthread_mutex_t lock;
} counter_t;

void counter_init(counter_t *c) {
    c->val = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void counter_inc(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->val++;
    pthread_mutex_unlock(&c->lock);
}

void counter_dec(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->val--;
    pthread_mutex_unlock(&c->lock);
}                                       


int counter_get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int val = c->val;
    pthread_mutex_unlock(&c->lock);
    return val;
}



typedef struct __myargs_t {
    int loops;
    counter_t *counter;
} myargs_t;

void *func(void *arg) {
    myargs_t *a = (myargs_t *) arg;
    int i;
    for (i = 0; i < a->loops; i++) {
        counter_inc(a->counter);
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc <= 2) {
        printf("enter two more args loops and threads" );
        return 1;
    }
    
    int loops, num_threads;
    loops = strtol(argv[1], NULL, 10);
    num_threads = strtol(argv[2], NULL, 10);
//    pthread_yield();

    pthread_t threads[num_threads];
    long time[num_threads];
    double total;
    int i, rc;
    counter_t counter;
    counter_init(&counter);
    myargs_t args;
    args.loops = loops;
    args.counter = &counter;
    struct timeval start, end;

    rc = gettimeofday(&start, NULL);

    for (i = 0; i < num_threads; i++) 
    {
        pthread_create(&threads[i], NULL, func, &args);
    }

    for (i = 0; i < num_threads; i++) 
    {
        pthread_join(threads[i], (void **) &time[i]);
    }

    rc = gettimeofday(&end, NULL);

    total = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    
    printf("%d threads incrementing a concurrent counter %d times each took %f seconds.\n\n",
            num_threads, loops, total / 1000000);
    return 0;
}

