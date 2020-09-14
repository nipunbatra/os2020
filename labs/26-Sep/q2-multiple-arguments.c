#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct arguments {
    int number;
    char *s;
} ;

void *print_thread(void *x)
{
    struct arguments *args = (struct arguments *)x;
    printf("%s, %d \n", args->s, args->number);
}

int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    struct arguments a1, a2;
    a1.number = 10;
    a1.s = "A";
    a2.number = 20;
    a2.s = "B";
    int rc1, rc2;
    printf("Inside main. Now creating the two threads\n");
    rc1 = pthread_create(&t1, NULL, print_thread, (void *)&a1);
    rc2 = pthread_create(&t2, NULL, print_thread, (void *)&a2);
    //sleep(0.05);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Exiting main\n");

    return 0;
}


