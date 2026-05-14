#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
int ft_popen(const char*f,char*const a[],char t){int fd[2];pid_t p;if(!f||!a||(t!='r'&&t!='w')||pipe(fd)<0)return-1;if((p=fork())<0){close(fd[0]);close(fd[1]);return-1;}if(!p){dup2(fd[t=='r'?1:0],t=='r');close(fd[0]);close(fd[1]);execvp(f,a);exit(1);}close(fd[t=='r'?1:0]);return fd[t=='r'?0:1];}
