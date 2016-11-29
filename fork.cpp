#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

void printDetails(){
	cout<<"PID :"<<getpid()<<endl;
	cout<<"Parent: "<<getppid()<<endl;
	cout<<"Real user ID:"<<getuid()<<endl;
	cout<<"Group ID: "<<getgid()<<endl;
	cout<<"Effective Group ID: "<<getegid()<<endl;
}
int main(){
	pid_t pid=fork();
	if(pid<0){
		cout<<"errorFork";
		return -1;
	}
	if(pid==0){
		cout<<"Child :"<<getpid()<<"\n----------\n";
		printDetails();
	}
	else{
		cout<<"Parent :"<<getpid()<<"\n----------\n";
		printDetails();
	
	}

}