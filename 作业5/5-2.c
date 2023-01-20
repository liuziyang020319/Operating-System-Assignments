#define __USE_GNU  
#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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
int data[5]={};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;/*初始化互斥锁*/
void *worker0(void *arg){
    int i;
    for(i=0;i<5;i++){
        pthread_mutex_lock(&mutex);
        printf("worker 0, time = %d:\n",i);
        for(int j=0;j<5;++j){
            data[j]=rand();
            printf("%d ",data[j]);
        }
        puts("");
        pthread_mutex_unlock(&mutex);
    }
}

void *worker1(void *arg){
    int i;
    for(i=0;i<5;i++){
        pthread_mutex_lock(&mutex);
        printf("worker 1, time = %d:\n",i);
        long long  ans = 0;
        for(int j=0;j<5;++j){
            ans += data[j];
        }
        printf("sum = %lld\n",ans);
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    
    pthread_t id_0, id_1;

    pthread_create(&id_0,NULL,worker0,NULL);
    pthread_create(&id_1,NULL,worker1,NULL);
    pthread_join(id_0,NULL);  
    pthread_join(id_1,NULL);

}
