#define __USE_GNU  
#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 1000000
#define numworker 2
int MAXT=1;
int arr[N+10];
int main(){
   for(int i=1;i<=N;++i)arr[i]=i;
   struct timespec t1 = {0, 0}; 
   struct timespec t2 = {0, 0}; 
   long sum = 0;
   clock_gettime(CLOCK_REALTIME, &t1);   
   while(MAXT--){
      
      for(int i=1;i<=N;++i)sum+=i;
   }

   clock_gettime(CLOCK_REALTIME, &t2);
   double duration=(t2.tv_sec - t1.tv_sec)*1000000000 + (t2.tv_nsec - t1.tv_nsec);
   printf("simple one, time = %.4lf ns sum = %ld\n",duration,sum);
   
   return 0;
}
