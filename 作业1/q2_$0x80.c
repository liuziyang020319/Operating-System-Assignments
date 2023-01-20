//https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit
//https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86-32_bit

#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
int main(){
    struct timespec t1 = {0, 0}; 
    struct timespec t2 = {0, 0}; 
    pid_t pid;
    int i;
    clock_gettime(CLOCK_REALTIME, &t1);

    asm volatile(
        "movl $39, %%eax\n\t"
        "syscall\n\t"  
        :"=a"(pid)
                /*第一个冒号后的限定字符串用于描述指令中的“输出”操作数。
                    刮号中的pid将操作数与C语言的变量联系起来。
                    "a":寄存器EAX。 
                    "b":寄存器EBX。 
                    "c":寄存器ECX。 
                    "d":寄存器EDX。
                */
    );        

    clock_gettime(CLOCK_REALTIME, &t2);
    double duration=(t2.tv_sec - t1.tv_sec)*1000000000 + (t2.tv_nsec - t1.tv_nsec);
    printf("time = %.4lf ns\n",duration);
    
    printf("current process's pid(ASM-64):%d %d\n",pid,getpid());

    clock_gettime(CLOCK_REALTIME, &t1);
    asm volatile(
        "mov $20, %%eax\n\t"
        "int $0x80\n\t"  
        :"=a"(pid)
                /*第一个冒号后的限定字符串用于描述指令中的“输出”操作数。
                    刮号中的pid将操作数与C语言的变量联系起来。
                    "a":寄存器EAX。 
                    "b":寄存器EBX。 
                    "c":寄存器ECX。 
                    "d":寄存器EDX。
                */
    );        
    clock_gettime(CLOCK_REALTIME, &t2);
    duration=(t2.tv_sec - t1.tv_sec)*1000000000 + (t2.tv_nsec - t1.tv_nsec);
    printf("time = %.4lf ns\n",duration);
    
    printf("current process's pid(ASM-32):%d %d\n",pid,getpid());
    return 0;
}