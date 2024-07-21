#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
int fd,ret;
char buffer[20];
fd=creat("example.txt",0644);
if(fd==-1){
perror("creat");
exit(EXIT_FAILURE);
}
ret=close(fd);
if(ret==-1){
perror("close");
exit(EXIT_FAILURE);
}
fd=open("example.txt",O_RDWR);
if(fd==-1){
perror("open");
exit(EXIT_FAILURE);
}
ret=lseek(fd,0,SEEK_SET);
if(ret==-1){
perror("lseek");
exit(EXIT_FAILURE);
}
ret=read(fd,buffer,13);
if(ret==-1){
perror("read");
exit(EXIT_FAILURE);
}
buffer[ret]='\0';
printf("Read from file :%s\n",buffer);
ret=close(fd);
if(ret==-1){
perror("close");
exit(EXIT_FAILURE);
}
return 0;
}
