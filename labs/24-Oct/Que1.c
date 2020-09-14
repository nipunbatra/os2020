#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<stdlib.h>
void main()
{
struct timeval start, end;
gettimeofday(&start, NULL);


for (int i = 0; i < 1000; i++)
    {
    }

gettimeofday(&end, NULL);

printf("printing time of day %ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));


}
