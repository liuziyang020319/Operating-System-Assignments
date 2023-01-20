#define __USE_GNU  
#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define N 10000000
#define numworker 2
int data[N+10];
int index = 0;

void *worker0(void *arg){
    int i;
    for(i=0;i<N;){
        int idx_temp = __sync_fetch_and_add(&index,200);
        for(int j=idx_temp; j<idx_temp + 200; ++j,i+=2){
            data[j] = i;  
        }
    }
}

void *worker1(void *arg){
    int i;
    for(i=0;i<N;){
        int idx_temp = __sync_fetch_and_add(&index,200);
        for(int j=idx_temp; j<idx_temp + 200; ++j,i+=2){
            data[j] = i + 1;  
        }
    }
}
int main(){
    pthread_t id_0, id_1;
    struct timespec t1 = {0, 0}; 
    struct timespec t2 = {0, 0}; 
    clock_gettime(CLOCK_REALTIME, &t1);   

    pthread_create(&id_0,NULL,worker0,NULL);
    pthread_create(&id_1,NULL,worker1,NULL);
    pthread_join(id_0,NULL);  
    pthread_join(id_1,NULL);

    clock_gettime(CLOCK_REALTIME, &t2);
    double duration=(t2.tv_sec - t1.tv_sec)*1000000000 + (t2.tv_nsec - t1.tv_nsec);
    printf("2 thread func , using __sync_fetch_and_add , time = %.4lf ns\n",duration);
    long long ans = -1;
    for(int i=1;i<N;i++){
        long long temp = data[i]- data[i-1];
        temp = temp > 0 ? temp : -temp;
        ans  = ans < temp ? temp : ans;
    }
    printf("ans = %lld , index = %d\n",ans,index);
    return 0;
}