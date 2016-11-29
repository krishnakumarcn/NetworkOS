#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
class Matrix{
	int a[10][10],m,n;
public:
	void read(){
		cout<<"Order: ";
		cin>>m>>n;
		cout<<"Matrix:\n";
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				cin>>a[i][j];
	}

	void display(){
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++)
				cout<<a[i][j]<<" ";
			cout<<"\n";
		}

	}
};
int main(){
	int shmid=shmget(IPC_PRIVATE,sizeof(Matrix)*3,0666);
	pid_t pid=fork();
	if(pid==0){
		Matrix *shmptr=(Matrix*)shmat(shmid,NULL,0);
		shmptr[0].read();
		shmptr[1].read();
	}
	else{
		wait(NULL);
		Matrix *shmptr=(Matrix*)shmat(shmid,NULL,0);
		shmptr[1].display();
	}

}