#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<limits.h>
#include<sys/time.h>

typedef struct __scounter_t {
    int64_t global;                 // the global total
    pthread_mutex_t glock;          // the global lock
    int local[8];             // the cpu local total
    pthread_mutex_t llock[8]; // the cpu local lock
    int threshold;                  // the max value stored in local, before transfering to global
} scounter_t;

void init(scounter_t *c, int threshold) {
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < 8; i++) {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

void update(scounter_t *c, int threadID, int amt) {
    int cpu = threadID % 8;
    pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {    // transfer local to global
        pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(&c->llock[cpu]);
}

int get(scounter_t *c) {
    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlock(&c->glock);
    return val;
}


typedef struct __myargs_t
 {
    int loops;
    scounter_t *counter;
    int mytid;
} myargs_t;

void *worker(void *arg) 
{
    myargs_t *a = (myargs_t *) arg;
    int i;
    for (i = 0; i < a->loops; i++) {
        update(a->counter, a->mytid, 1);
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc <= 3)
 {
     printf("Enter three arguments: Number of Loops, Number of threads, Threshold \n");
     return 1;
    }
    
    int loops, num_threads, threshold;
    loops = strtol(argv[1], NULL, 10);
    num_threads = strtol(argv[2], NULL, 10);
    threshold = strtol(argv[3], NULL, 10);
    printf("Number of threads:\t%d\nNumber of loops:\t%d\nSize of threshold:\t%d\n",
            num_threads, loops, threshold);

    pthread_t threads[num_threads];
    long time[num_threads];
    double total;
    int i, rc;
    scounter_t counter;
    init(&counter, threshold);
    myargs_t args[num_threads];
    struct timeval start, end;

    rc = gettimeofday(&start, NULL);

    for (i = 0; i < num_threads; i++) {
        args[i].mytid = i;      // thread ID
        args[i].loops = loops;
        args[i].counter = &counter;
        pthread_create(&threads[i], NULL, worker, &args[i]);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], (void **) &time[i]);
    }

    rc = gettimeofday(&end, NULL);

    total = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    
    printf("%d threads incrementing a sloppy counter %d times each took %f seconds.\n\n",
            num_threads, loops, total / 1000000);

    return 0;

}
