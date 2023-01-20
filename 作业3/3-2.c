#define __USE_GNU  
#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 1000000
#define numworker 2
int arg0[2] = {numworker,0};//numworker线程数，告知程序for循环运行的补偿0/1代表填偶数还是奇数
int arg1[2] = {numworker,1};//
int arr[N+10];
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

    for(int i=res;i<=N;i+=mod){
      arr[i]=i;
    }
}

int main(){
    struct timespec t1 = {0, 0}; 
    struct timespec t2 = {0, 0}; 
    clock_gettime(CLOCK_REALTIME, &t1);   
   
    pthread_t id_0,id_1;
    pthread_create(&id_0,NULL,worker,arg0);//id_0将所有偶数填满
    pthread_create(&id_1,NULL,worker,arg1);//id_1将所有奇数填满

    pthread_join(id_0,NULL);  
    pthread_join(id_1,NULL);//pthread_join是阻塞等待子线程执行完毕，所以使用此功能可以保证arr已经被写入完毕
    long long sum = 0;
    for(int i=1;i<=N;++i)sum+=arr[i];  
    for(int i=1;i<=N;++i)printf("%d ",arr[i]);
    puts("");

    clock_gettime(CLOCK_REALTIME, &t2);
    double duration=(t2.tv_sec - t1.tv_sec)*1000000000 + (t2.tv_nsec - t1.tv_nsec);
    printf("2 thread func , time = %.4lf ns sum=%lld\n",duration,sum);

   
    return 0;
}
