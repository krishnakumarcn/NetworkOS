#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

int main(){
	int pipefd[2];
	if(pipe(pipefd)==-1){
		cout<<"PipeError!";
		return -1;
	}
	pid_t pid=fork();
	if(pid<0){
		cout<<"ForkError!";
		return -1;
	}
	
	int n1,n2;
	int num[100],numbers[100];
	
	if(pid==0){
		cout<<"n";
		cin>>n1;
		close(pipefd[0]);
		cout<<"Enter the Elements :";
		for(int i=0;i<n1;i++){
			cin>>num[i];
		}
		write(pipefd[1],&n1,sizeof(int));
		write(pipefd[1],num,sizeof(int)*n1);
		
	}
	else{
		wait(NULL);
		close(pipefd[1]);
		read(pipefd[0],&n2,sizeof(int));
		read(pipefd[0],numbers,sizeof(int)*n2);
		for(int i=0;i<n2;i++)
			cout<<numbers[i]<<" -- ";
		cout<<endl;
	}

}