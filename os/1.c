a)
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
 pid_t pid;
 int status;
 
 pid =fork();
 if(pid<0){
 printf("Error :fork() failed.\n");
 return 1; }
 else if(pid==0){
 printf("This is the child process with PID:%d\n",getpid());
 printf("Parent process PID:%d\n",getpid());
 execlp("/bin/ls","ls",NULL);
 printf("This should not be printed if exec() is successful.\n");
 return 0; }
 else{
 printf("This is the parent process with PID:%d\n",getpid());
 printf("Child process PID:%d\n",pid);
 wait(&status);
 printf("Child process exited the status:%d\n",status);
 return 0;
 }
}



b) vfork()
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(){
 pid_t pid;
 pid =vfork();
 if(pid==-1){
 perror("vfork");
 return 1;
 }
 else if(pid==0){
 printf("Child process :Hello,I'm the child!\n");
 printf("Child process :My PID is %d\n",getpid());
 printf("Child process :My parent's PID is %d\n",getppid());
 _exit(0);
 }
 else{
 
printf("Parent process :Hello,I'm the Parent!\n");
 printf("Parent process :My PID is %d\n",getpid());
 printf("Parent process :My child's PID is %d\n",pid);
 int status;
 waitpid(pid,&status,0);
 if(WIFEXITED(status)){
 printf("Parent process :Child process terminated normally.\n");
 }
 else{
 printf("Parent process :Child process terminated abnormally.\n");
 }
 }
 return 0;
}
