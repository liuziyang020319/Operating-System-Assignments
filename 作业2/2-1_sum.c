#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char **argv){
    printf("argc :%d\n",argc);
    argv++;
    int tot = (*argv)[0];
    printf("%d\n",tot);
    argv++;
    int ans=0;
    char * sum = *argv;
    for(int i=0;i<tot;++i){
        printf("%d ",sum[i]);
        ans+=sum[i];
    }
    puts("");
    printf("this is the child process , sum num = %d, pid = %d, fa pid = %d\n",ans,getpid(),getppid());
    argv++;
    system(*argv);
    return 0;
}