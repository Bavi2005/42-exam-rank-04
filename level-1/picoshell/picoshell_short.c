#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int picoshell(char **c[]){int i=0,in=0,fd[2],p,s;while(c&&c[i]){if(c[i+1]&&pipe(fd)<0)return 1;if((p=fork())<0)return 1;if(!p){if(in){dup2(in,0);close(in);}if(c[i+1]){dup2(fd[1],1);close(fd[0]);close(fd[1]);}execvp(c[i][0],c[i]);exit(1);}if(in)close(in);if(c[i+1]){close(fd[1]);in=fd[0];}i++;}while(wait(&s)>0)if(!WIFEXITED(s)||WEXITSTATUS(s))return 1;return 0;}
