#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
using namespace std;
/*
create sockaddr_in type
set sockaddr_in type
create socket
connect
read/write
*/
int main(){
	struct sockaddr_in servAddr;
	char buffer[256];
	int portno=5000;
	int sockfd;
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(portno);
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	int n=connect(sockfd,(struct sockaddr*) &servAddr,sizeof(servAddr));
	if(n<0){
		cout<<"ErrorConnection!!";
		return 0;
	}
	cout<<"      ChatBox\n   -------------\n";
	while(1){
		bzero(buffer,256);
		cout<<"\nYou: ";
		cin>>buffer;
		write(sockfd,buffer,strlen(buffer));
		cout<<"\nUnknown: ";
		bzero(buffer,256);
		read(sockfd,buffer,255);
		cout<<buffer;
	}

}