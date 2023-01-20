#define __USE_GNU  
#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 1000000
#define numworker 2
int arg0[2] = {numworker,0};
int arg1[2] = {numworker,1};
int arr[N+10];
int MAXT = 1;
//线程执行的函数
void *worker(void *arg){
   int tot = N;
   int * argnow = arg;
   int mod = argnow[0];
   int res = argnow[1];
cpu_set_t cpuset;   //CPU核的位图
   CPU_ZERO(&cpuset);  //将位图清零
   CPU_SET(res, &cpuset);  //设置位图第N位为1，表示与core N绑定。N从0开始计数
   sched_setaffinity(0, sizeof(cpuset), &cpuset);  //将当前线程和cpuset位图中指定的核绑定运行

   long * ret = (long *) malloc(sizeof (long ));
   for(int i=res;i<=N;i+=mod){
      (*ret) += arr[i];
   }
   return ret;
}

int main(){
   for(int i=0;i<=N;++i)arr[i]=i;
   struct timespec t1 = {0, 0}; 
   struct timespec t2 = {0, 0}; 
   clock_gettime(CLOCK_REALTIME, &t1);   
   
   while(MAXT--){
      pthread_t id_0,id_1;
      int * ret0, *ret1;
      pthread_create(&id_0,NULL,worker,arg0);
      pthread_create(&id_1,NULL,worker,arg1);
      void * res0, *res1;

      pthread_join(id_0,&res0);  
      pthread_join(id_1,&res1);

      long sum = *(long *)res0 + *(long *)res1;      
      printf("%ld\n",sum);
   }

   clock_gettime(CLOCK_REALTIME, &t2);
   double duration=(t2.tv_sec - t1.tv_sec)*1000000000 + (t2.tv_nsec - t1.tv_nsec);
   printf("2 thread func , time = %.4lf ns\n",duration);

   
   return 0;
}
