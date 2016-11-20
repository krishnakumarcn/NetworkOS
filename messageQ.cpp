#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

using namespace std;

struct msgbuff{
	long mtype;
	char mbuff[10];
}msg1,msg2;

int main(){
	msg1.mtype=1;
	msg2.mtype=2;

	pid_t pid=fork();
	if(pid<0){
		return -1;
	}
	//child
	if(pid==0){
		cout<<"Send: ";
		int msgid_s=msgget(7079,IPC_CREAT|0666);
		cin>>msg1.mbuff;
		msgsnd(msgid_s,&msg1,sizeof(msg1.mbuff),0);
	}
	else{
		int msgid_r=msgget(7079,IPC_CREAT|0666);
		msgrcv(msgid_r,&msg2,sizeof(msg2.mbuff),1,0);
		cout<<"Recieved: "<<msg2.mbuff;
	}

	return 0;
}