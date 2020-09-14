#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
//#include "llist.h"




typedef struct __counter_t {
    int val;
    pthread_mutex_t lock;
} counter_t;


void counter_init(counter_t *c) {
    c->val = 0;
    pthread_mutex_init(&c->lock, NULL);
}

int counter_inc_and_get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->val++;
    int val = c->val;
    pthread_mutex_unlock(&c->lock);
    return val;
}


typedef struct __node_t {
    int key;
    struct __node_t *next;
    pthread_mutex_t lock;
} node_t;

typedef struct __llist_t {
    node_t *head;
    pthread_mutex_t lock;
} llist_t;

/* ll_init: initialize the new list */
void ll_init(llist_t *l) {
    pthread_mutex_init(&l->lock, NULL);
    l->head = NULL;
}

/* ll_insert: create a new node with the value of key and
 *      prepend it to the front of the list
 */
int ll_insert(llist_t *l, int key) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {    // check malloc success
        return -1;
    }
    new->key = key;
    pthread_mutex_init(&new->lock, NULL);
    pthread_mutex_lock(&l->lock);   // get llist_t lock
    new->next = l->head;
    l->head = new;
    pthread_mutex_unlock(&l->lock); // release lock
    return 0;
}


int ll_indexof(llist_t *l, int key) {
    pthread_mutex_lock(&l->lock);       // get llist_t lock
    if (l->head == NULL) {              // if the list is empty
        pthread_mutex_unlock(&l->lock); // release llist_t lock and exit
        return -1;
    }
    node_t *node = l->head;
    pthread_mutex_lock(&node->lock);   // get first node lock
    pthread_mutex_unlock(&l->lock);    // release llist_t lock
    int i;
    for (i = 0; node->key != key; i++) {
        if (!node->next) {
            i = -1;
            break;
        }
        pthread_mutex_lock(&node->next->lock); // get next node's lock
        pthread_mutex_unlock(&node->lock);     // unlock this node's lock
        node = node->next;
    }
    pthread_mutex_unlock(&node->lock);  // release node lock
    return i;
}


typedef struct __myargs_t {
    int loops;
    counter_t *counter;
    int mytid;
    llist_t *list;
    int key;
} myargs_t;

void *build_list(void *arg) {
    myargs_t *a = (myargs_t *) arg;
    int i, key;
    for (i = 0; i < a->loops; i++) {
        key = counter_inc_and_get(a->counter);
        ll_insert(a->list, key);
    }
    return NULL;
}

void *search_list(void *arg) {
    myargs_t *a = (myargs_t *) arg;
    int rc;
    double total;
    struct timeval start, end;

    rc = gettimeofday(&start, NULL);         // set timer
    int index = ll_indexof(a->list, a->key); // find the key
    rc = gettimeofday(&end, NULL);           // end timer
    total = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    printf("%d was found at index %d by thread #%d in %f seconds\n", 
            a->key, index, a->mytid, total / 1000000);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc <= 2) {
        printf("Enter 2 more arguments, number of loops and number of threads\n");
        return 0;
    }
    
    int loops, num_threads;
    loops = strtol(argv[1], NULL, 10);
    num_threads = strtol(argv[2], NULL, 10);

    pthread_t threads[num_threads];
    int i;
    counter_t counter;
    counter_init(&counter);
    llist_t list;
    ll_init(&list);
    myargs_t args[num_threads];

    // build the list
    for (i = 0; i < num_threads; i++) {
        args[i].mytid = i;      // thread ID
        args[i].loops = loops;
        args[i].counter = &counter;
        args[i].list = &list;
        pthread_create(&threads[i], NULL, build_list, &args[i]);
    }
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    for (i = 0; i < num_threads; i++) {
        args[i].key = (num_threads * loops) / (num_threads - i);
        pthread_create(&threads[i], NULL, search_list, &args[i]);
    }
    for (--i; i >= 0; i--) {
        pthread_join(threads[i], NULL);
    }

    int exp = num_threads * loops;
    return 0;
}
