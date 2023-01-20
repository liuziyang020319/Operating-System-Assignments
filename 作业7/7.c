#define __USE_GNU  
#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdatomic.h>
#define TASKNUM (16)
typedef struct STA{
    int sum;
    struct STA * nxt;
}STA;
int GetTop(STA *S){
    if(S->sum == 0){
        return 0;
    }
    else{
        return S->nxt->sum;
    }
}
void Pop(STA *S){
    if(S->nxt == NULL)return;
    S->nxt = S->nxt->nxt;
    (S->sum) --;
}
void Ins(STA *S,int sum){
    STA * now = (STA *)malloc(sizeof(STA));
    now->sum = sum;
    now->nxt = S->nxt;
    S->nxt   = now;
    (S->sum)++;
}
typedef struct {
    STA *S;
    pthread_mutex_t mutex; 
    pthread_cond_t  cond;
    int remind;
}Monitor_NODE;
void Moniter_init(Monitor_NODE * Monitor){
    pthread_mutex_init(&(Monitor->mutex),NULL);
    pthread_cond_init (&(Monitor->cond) ,NULL);
    Monitor->remind = TASKNUM;  
    
    Monitor->S = (STA *)malloc(sizeof(STA));

    Monitor->S->nxt = NULL;
    Monitor->S->sum = 0;
    
    for(int i = 0; i<TASKNUM; i++){
        int x = rand()%20;
        Ins(Monitor->S,x);
    }
}

typedef struct {
    int first,second,a,b;
}RETNODE;


RETNODE Monitor_getTASK(Monitor_NODE * Monitor){
    RETNODE ret;
    pthread_mutex_lock(&(Monitor->mutex));
    if((Monitor->remind) == 1){
        pthread_mutex_unlock(&(Monitor->mutex));
        ret.first = 0;
        ret.second= 0;
        ret.a=ret.b=0;
        return ret;
    }
    (Monitor->remind)--;
    while(Monitor->S->sum < 2){
        pthread_cond_wait(&(Monitor->cond),&(Monitor->mutex));
    }
    int a = GetTop(Monitor->S);
    Pop(Monitor->S);
    int b = GetTop(Monitor->S);
    Pop(Monitor->S);    
    pthread_mutex_unlock(&(Monitor->mutex));
    ret.first = 0;
    ret.second= 1; 
    ret.a     = a;
    ret.b     = b; 
    return ret;
}

void Monitor_putResult(Monitor_NODE * Monitor,int x){
    pthread_mutex_lock(&(Monitor->mutex));
    Ins(Monitor->S,x);
    if(Monitor->S->sum == 2){
        pthread_cond_signal(&(Monitor->cond));
    }
    pthread_mutex_unlock(&(Monitor->mutex));
}

void *worker(void *arg){
    long * argnow = arg;
    long id = argnow[0];
    Monitor_NODE * Monitor = argnow[1];
    // printf("%d %p\n",id,Monitor);
    // return NULL;
    while(1){
        RETNODE now = Monitor_getTASK(Monitor);
        if(now.second == 0){
            printf("thread %d finished\n",id);
            return NULL;
        }
        else{
            int a = now.a;
            int b = now.b;    
            usleep(rand()%10);
            int c = a + b;
            printf("thread %d %d+%d=%d\n",id,a,b,c);
            Monitor_putResult(Monitor,c);
        }
    }
}
pthread_t thread[9];
atomic_long arg[8][3];
int main(){
    srand(time(0));
    Monitor_NODE* Monitor;
    Monitor = malloc(sizeof(Monitor_NODE));  
    Moniter_init(Monitor);
    STA * now = Monitor->S;
    int Target = 0;
    for(now=now->nxt;now;now=now->nxt){
        printf("%d ",now->sum);
        Target += now->sum;
    }
    puts("");
    puts("============== TASK begin ==============");
    
    for(atomic_long i=0;i<8;i++){
        arg[i][0] = i;
        arg[i][1] = Monitor;
        pthread_create(&(thread[i]),NULL,worker,arg[i]);
        // usleep(1);
    }

    for(int i=0;i<8;i++){
        pthread_join((thread[i]),NULL);
    }
    now = Monitor->S;
    printf("Reduce sum = %d Target = %d\n",now->nxt->sum,Target);  
    return 0;
}