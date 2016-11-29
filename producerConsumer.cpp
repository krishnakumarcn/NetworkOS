#include<iostream>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<random>
#define BUFFER_SIZE 5

using namespace std;
int index=0;
int buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t full,empty;

void* produce(void *arg){
  int count=0;
  while(count++<10){
    //    sleep(1);
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    int item=rand()%100;
    buffer[index++]=item;
    cout<<"produced"<<item<<endl;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
  }

}

void* consume(void* arg){
  int count=0;
  while(count++<10){
    // sleep(1);
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    int item=buffer[--index];
    cout<<"Consumed "<<item<<endl;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }
}
int main(){
  pthread_t producer,consumer;
  sem_init(&empty,0,BUFFER_SIZE);
  sem_init(&full,0,0);
  pthread_mutex_init(&mutex,NULL);
  pthread_create(&producer,NULL,produce,NULL);
  pthread_create(&consumer,NULL,consume,NULL);
  pthread_exit(NULL);
  return 0;
}
