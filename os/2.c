write.c
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(){
 
 int fd;
 char *myfifo="/tmp/myfifo";
 mkfifo(myfifo,0666);
 fd=open(myfifo,O_WRONLY);
 write(fd,"Hello", sizeof('Hello'));
 close(fd);
 unlink(myfifo);
 return 0;
}



read.c
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#define MAX_BUF 1024
int main(){
 
 int fd;
 char *myfifo="/tmp/myfifo";
 char buf[MAX_BUF];
 fd=open(myfifo,O_RDONLY);
 read(fd,buf,MAX_BUF);
 printf("Received:%s\n",buf);
 close(fd);
 return 0;
}
