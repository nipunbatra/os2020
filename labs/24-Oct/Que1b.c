#include <time.h>
#include<stdio.h>
int main()
{
   clock_t start = clock();
   //... do work here
   clock_t end = clock();
   double time_elapsed_in_seconds = (end - start)/(double)CLOCKS_PER_SEC;
   printf("Printing Time of day ising clock timer%lf\n",time_elapsed_in_seconds);
   return 0;
}
