#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

void *print_thread(void *x)
{
    int a = (int) x;
    //for (int i=0; i<20; i++) printf("-");
    printf("Thread %d", a);
    //for (int i=0; i<20; i++) printf("-");
    printf("\n");
    // Define a local variable and print its address
    //int loc = 10;
    //printf("Address of the local variable is:%p\n", &loc);
    
}

int main(int argc, char const *argv[])
{
    // Define a local variable and print its address
    int loc = 10;
    printf("Address of the local variable in main is:%p\n", &loc);
    pthread_t t[20];
    int rc[20];
    printf("Inside main. Now creating the 20 threads\n");
    for (int t_no = 0; t_no<20; t_no++)
    {    
        rc[t_no] = pthread_create(&t[t_no], NULL, print_thread, (void *)t_no);
    }
    for (int t_no = 0; t_no<20; t_no++)
    {
       pthread_join(t[t_no], NULL);
    }

    printf("Exiting main\n");

    return 0;
}


