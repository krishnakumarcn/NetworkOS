#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

/*

Create socket
Set sockaddr_in objects
bind
listen
accept
read/write

*/
int main(){
	struct sockaddr_in servAddr,cliAddr;
	int portno=5000;

	//create socket
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		cout<<"errorCreatingSocket";
		return -1;
	}

	bzero((char*)&servAddr,sizeof(servAddr));

	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(portno);
	servAddr.sin_addr.s_addr=INADDR_ANY;
	
	//bind
	if( bind(sockfd,(struct sockaddr *)	&servAddr, sizeof(servAddr)) < 0){
		cout<<"errorBinding";
		return -1;
	}

	//listen
	listen(sockfd, 5);
	
	//accept
	socklen_t cliientAdress=sizeof(cliAddr);
	int newsockfd=accept(sockfd,(struct sockaddr*)&cliAddr , &cliientAdress );

	if(newsockfd<0){
		cout<<"acceptFailed";
		return -1;
	}
	cout<<"      ChatBox\n   -------------\n";
	char buffer[256];

	//read & write
	while(1){
		bzero(buffer,256);
		int n=read(newsockfd,buffer,255);
		if(n<0){
			cout<<"errorReadingFromSocket";
		}
		cout<<"\nUnknown: "<<buffer<<endl;
		bzero(buffer,256);
		cout<<"\nYou: ";
		cin>>buffer;
		n=write(newsockfd,buffer,255);
		if(n<0){
			cout<<"errorWritingToSocket";
			return -1;
		}
	}

}