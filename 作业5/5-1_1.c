#define __USE_GNU  
#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdatomic.h>
/*
index = 0
//thread0 
for(i=0;i<MAX;i+=2) {
    data[index] = i; //even ( i+1 for thread 2) 
    index++;
}
//thread1 
for(i=0;i<MAX;i+=2) {
    data[index] = i+1; //odd 
    index++;
}
*/
#define N 10000000
#define numworker 2
#define bool unsigned char
#define true  1
#define false 0
int data[N+10];
//线程执行的函数
atomic_int turn = -1;
int index_num = 0;
bool flag[numworker];
void *worker0(void *arg){
    // int i;
    for(int i=0;i<N;i+=2){
        if(i%400==0){
            flag[0]=true;
            turn = 1;
            while(flag[1] == true && turn == 1);
            //lock
        }
        data[index_num] = i;
        index_num = index_num + 1;
        if(i%400==398){
            flag[0]=false;//unlock
        }
    }
    return NULL;
}

void *worker1(void *arg){
    // int i;
    for(int i=0;i<N;i+=2){
        if(i%400==0){//lock
            flag[1]=true;
            turn = 0;
            while(flag[0] == true && turn == 0);
        }
        data[index_num] = i + 1;
        index_num = index_num + 1;
        if(i%400==398){
            flag[1]=false;
        }
    }
    return NULL;
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
    printf("2 thread func , time = %.4lf ns\n",duration);
    long long ans = -1;
    for(int i=1;i<N;i++){
        long long temp = data[i]- data[i-1];
        temp = temp > 0 ? temp : -temp;
        ans  = ans < temp ? temp : ans;
    }
    printf("ans = %lld , index_num = %d\n",ans,index_num);
}
