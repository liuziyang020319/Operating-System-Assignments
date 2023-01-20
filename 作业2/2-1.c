#include<unistd.h>
#include<sys/wait.h>
#include <sys/types.h>
#include<stdio.h>
#include<stdlib.h>
char sum[10];
static void testExecv() {
    char tot[1]={10};
    char *cmdstring="ls -l";
    char *argv[] = {"sum",tot,sum,cmdstring,(char*)NULL};
    int result = execv("/mnt/c/Users/lzy/Desktop/大三/操作系统/作业2/sum", argv);
    if (result == -1) {
        perror("execl error");
    }
}
int main(){
    for(int i=0;i<10;++i)sum[i]=i+1;
    pid_t pid;
    pid = fork();
    int status,id;
    if(pid == -1){
        perror("fork error");
        exit(-1);
    }
    else if(pid==0){
        testExecv();
        exit(1);
    }
    else if(pid>0){
        printf("parent process: pid=%d, wait for child\n",getpid());
        pid = wait(&status);
        id = WEXITSTATUS(status); 
        printf("parent process finishes, child's pid = %d . exit status = %d\n",pid,id);
    } 
    return 0;  
}