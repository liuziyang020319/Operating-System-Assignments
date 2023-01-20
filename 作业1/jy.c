#include "stdio.h"
#include "unistd.h"
#include "sys/syscall.h"
#include "time.h"

int main(){
    struct timespec time1,time2;
    
    // glibc
    pid_t pid1;
    printf("Getpid via glibc:        ");
    clock_gettime(CLOCK_REALTIME,&time1);
    pid1 = getpid();
    clock_gettime(CLOCK_REALTIME,&time2);
    printf("pid %d\t",pid1);
    printf("time %d\n",time2.tv_nsec-time1.tv_nsec);

    // syscall
    pid_t pid2;
    printf("Getpid via syscall:      ");
    clock_gettime(CLOCK_REALTIME,&time1);
    pid2 = syscall(SYS_getpid);
    clock_gettime(CLOCK_REALTIME,&time2);
    printf("pid %d\t",pid2);
    printf("time %d\n",time2.tv_nsec-time1.tv_nsec);

    // asm
    pid_t pid3;
    printf("Getpid via asm syscall:  ");
    clock_gettime(CLOCK_REALTIME,&time1);
    long long in=SYS_getpid;
    asm volatile(
        "movq %1, %%rax; syscall;"
        :"=a"(pid3)
        :"g"(in)
    );
    clock_gettime(CLOCK_REALTIME,&time2);
    printf("pid %d\t",pid3);
    printf("time %d\n",time2.tv_nsec-time1.tv_nsec);   
}