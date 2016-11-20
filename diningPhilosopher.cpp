//correct program

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t chopstick[5];
pthread_t threads[5];
void* eat(void* num){
	int* number=(int*) num;
	int n=*number;
	cout<<"\nThinking :"<<n;
	sem_wait(&chopstick[n]);
	sem_wait(&chopstick[(n+1)%5]);
	cout<<"\nEating :"<<n;
	sleep(3);
	sem_post(&chopstick[n]);
	sem_post(&chopstick[(n+1)%5]);
	cout<<"\nFinished : " <<n;

}

int main(){
	for(int i=0;i<5;i++)
		if(sem_init(&chopstick[i],0,1)==-1){
			cout<<"errorInitSem";
			return -1;
		}
	int n[5];
	for(int i=0;i<5;i++){
		n[i]=i;
		int id=pthread_create(&threads[i],NULL,eat,&n[i]);
	}
	pthread_exit(NULL);
	return 0;
}