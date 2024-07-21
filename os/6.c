#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_PHILOSOPHERS 5
int buffer[BUFFER_SIZE];
int in =0;
int out = 0;
sem_t emptySlots;
sem_t filledSlots;
sem_t bufferMutex;
sem_t mutex;
sem_t rwMutex;
void *producer(void *producerId )
{
int id = *(int *)producerId;
int item=0;
while(1){
item++;
sem_wait(&emptySlots);
sem_wait(&bufferMutex);
buffer[in]=item;
printf("Producer %d produced item %d\n",id,item);
in = (in+1)%BUFFER_SIZE;
sem_post(&bufferMutex);
sem_post(&filledSlots);
usleep(rand() % 1000000);
}
}
void *consumer(void *consumerId){
int id=*(int *)consumerId;
int item;
while(1){
sem_wait(&filledSlots);
sem_wait(&bufferMutex);
item=buffer[out];
printf("Consumer %d consumed item %d\n",id,item);
out=(out+1) %BUFFER_SIZE;
sem_post(&bufferMutex);
sem_post(&emptySlots);
usleep(rand() % 1000000);
}
}
enum {THINKING,HUNGRY,EATING}state[5];
sem_t philMutex;
sem_t philSem[5];
void test (int id)
{
if(state[id] == HUNGRY && state[(id+1)%5]!=EATING && state[(id+4)%5]!=EATING)
{
state[id]=EATING;
sem_post(&philSem[id]);
}
}
 
void *philosopher(void *philosopherId)
{
int id=*(int *)philosopherId;
while(1)
{
printf("Philosopher %d is thinking\n" ,id);
usleep(rand() % 1000000);
sem_wait(&philMutex);
state[id]=HUNGRY;
printf("Philosopher %d is hungry\n",id);
test(id);
sem_post(&philMutex);
sem_wait(&philSem[id]);
printf("Philosopher %d is eating\n" ,id);
usleep(rand() % 1000000);
sem_post(&philSem[id]);
printf("Philosopher %d finished eating\n" ,id);
}
}
int main(){
sem_init(&emptySlots,0,BUFFER_SIZE);
sem_init(&filledSlots,0,0);
sem_init(&bufferMutex,0,1); 
pthread_t producers[NUM_PRODUCERS];
pthread_t consumers[NUM_CONSUMERS]; 
int producerIds[NUM_PRODUCERS];
int consumerIds[NUM_CONSUMERS]; 
for(int i=0;i<NUM_PRODUCERS;i++){
producerIds[i]=i+1;
pthread_create(&producers[i],NULL,producer,(void *)&producerIds[i]);
}
for(int i=0;i<NUM_CONSUMERS;i++){
consumerIds[i]=i+1;
pthread_create(&consumers[i],NULL,consumer,(void *)&consumerIds[i]);
}
sem_init(&philMutex,0,1);
pthread_t philosophers[NUM_PHILOSOPHERS];
int philosopherIds[NUM_PHILOSOPHERS];
for(int i=0;i<NUM_PHILOSOPHERS;i++)
{
philosopherIds[i]=i+1;
sem_init(&philSem[i],0,0);
pthread_create(&philosophers[i],NULL,philosopher,(void *)&philosopherIds[i]);
}
for(int i=0;i<NUM_PRODUCERS;i++)
{ pthread_join(producers[i],NULL);
}
for(int i=0;i<NUM_CONSUMERS;i++)
{ pthread_join(consumers[i],NULL);
} 
for(int i=0;i<NUM_PHILOSOPHERS;i++)
{
pthread_join(philosophers[i],NULL);
}
sem_destroy(&emptySlots); 
sem_destroy(&filledSlots); 
sem_destroy(&bufferMutex); 
sem_destroy(&mutex); 
sem_destroy(&rwMutex); 
sem_destroy(&philMutex); 
for(int i=0;i<NUM_PHILOSOPHERS;i++)
{
sem_destroy(&philSem[i]);
}
return 0;
}
