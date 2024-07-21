1)FCFS
#include<stdio.h>
#include<stdlib.h>
int main(){
int n,i,head,total=0;
printf("enter the no.of requests:");
scanf("%d",&n);
int requests[n];
printf("enter the request queue:\n");
for(i=0;i<n;i++)
{
scanf("%d",&requests[i]);
}
printf("enter the initial head positon:");
scanf("%d",&head);
printf("head movement order:\n");
for(i=0;i<n;i++){
printf("%d ->",head);
total+=abs(requests[i]-head);
head=requests[i];
}
printf("%d ->",head);
printf("End\n");
printf("total head movements %d\n",total);
return 0;
}


2)SCAN
#include<stdio.h>
#include<stdlib.h>
int main(){
int n,i,head,direction,total=0,f;
printf("Enter the no.o requests:");
scanf("%d",&n);
int requests[n];
printf("Enter the request queue:\n");
for(i=0;i<n;i++)
{
scanf("%d",&requests[i]);
}
printf("Enter the initial head position:");
scanf("%d",&head);
printf("Enter the direction(0 for left,1 for right):");
scanf("%d",&direction);
for(i=0;i<n-1;i++)
{
for(int j=0;j<n-i-1;j++)
{
if(requests[j]>requests[j+1])
{
int temp=requests[j];
requests[j]=requests[j+1];
requests[j+1]=temp;
}
}
}
int current=head;
if(direction==1)
{
for(i=0;i<n;i++)
{
if(requests[i]>=head)
{
break;
}
}
}
else{
for(i=n-1;i>=0;i--)
{
if(requests[i]<=head)
{
break;
}
}
}
f=i;
printf("Head Movement Order:\n");
if(direction==1)
{
for(;i<n;i++)
{
printf("%d->",current);
total+=abs(requests[i]-current);
current=requests[i];
}
if(current==requests[n-1])
{
printf("%d->",requests[n-1]);
total+=abs(199-requests[n-1]);
printf("199->");
current=199;
}
for(i=f-1;i>=0;i--)
{
total+=abs(requests[i]-current);
current=requests[i];
printf("%d->",current);
}
}
else{
for(;i>=0;i--)
{
printf("%d->",current);
total+=abs(requests[i]-current);
current=requests[i];
}
printf("%d->",current);
if(current==requests[0])
{
total+=abs(current-0);
printf("0->");
current=0;
}
for(i=f+1;i<n;i++)
{
total+=abs(requests[i]-current);
current=requests[i];
printf("%d->",current);
}
}
printf("End\n");
printf("Total head movements:%d\n",total);
return 0;
}
