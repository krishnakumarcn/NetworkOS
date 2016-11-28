#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
using namespace std;

int main(){
	sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		cout<<"errorConnection!";
		return -1;
	}

	char buffer[256];
	ifstream fp("toSend.txt");
	while(!fp.eof()){
		fp.getline(buffer,255,'\n');
		//cout<<"|| "<<buffer<<" ||";
		write(sockfd,buffer,255);

	}	
	buffer[0]='\0';
	write(sockfd,buffer,strlen(buffer));
	cout<<"File Sent.";
	fp.close();
	return 0;
}