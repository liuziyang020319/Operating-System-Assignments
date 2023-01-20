#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
int main(){
    struct timespec t1 = {0, 0}; 
    struct timespec t2 = {0, 0}; 

    pid_t pid;

    clock_gettime(CLOCK_REALTIME, &t1);
    
    pid = getpid();

    clock_gettime(CLOCK_REALTIME, &t2);
    double duration=(t2.tv_sec - t1.tv_sec)*1000000000 + (t2.tv_nsec - t1.tv_nsec);
    printf("time = %.4lf ns\n",duration);
    
    printf("current process's pid(getpid):%d %d\n",pid,getpid());
    return 0;
}