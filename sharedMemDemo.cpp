#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){

	int shmid=shmget(IPC_PRIVATE,sizeof(int),0666);
	int *shmptr1,*shmptr2;
	pid_t pid;
	pid=fork();
	if(pid<0){
		cout<<"errorForking";
		return -1;
	}
	int a=10;
	//child
	if(pid==0){
		shmptr1=(int*)shmat(shmid,NULL,0);
		*shmptr1=10;
	}
	//parent
	else{
		wait(NULL);
		shmptr2=(int*)shmat(shmid,NULL,0);
		cout<<*shmptr2<<endl;
	}

	return 0;
}