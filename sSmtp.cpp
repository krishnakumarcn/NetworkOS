#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
using namespace std;

struct mail{
	char to[256];
	char from[256];
	char sub[1024];
	char content[1024];
}m;
int main(){

	int sockfd=socket(PF_INET,SOCK_DGRAM,0);
	sockaddr_in servaddr;
	//bzero((char*)servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	cout<<"From:   ";
	cin>>m.from;
	cout<<"To:     ";
	cin>>m.to;
	cout<<"Sub:    ";
	cin>>m.sub;
	cout<<"Content:";
	cin>>m.content;
	socklen_t clilen=sizeof(servaddr);
	int n=sendto(sockfd,&m,sizeof(m),0,(struct sockaddr*)&servaddr,clilen);
	char buffer[100];
	int n2=recvfrom(sockfd,&buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,&clilen);
		cout<<"\n----------\n"<<buffer<<"-----------\n";
	return 0;

}