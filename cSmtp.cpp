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
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	socklen_t clilen=sizeof(servaddr);
	int n=recvfrom(sockfd,&m,sizeof(m),0,(struct sockaddr*)&servaddr,&clilen);
	
	cout<<"One Unread Mail..";
	cout<<"\nTo:      "<<m.to;
	cout<<"\nFrom     "<<m.from;
	cout<<"\nSub:     "<<m.sub;
	cout<<"\nContent: "<<m.content;
	char buffer[100]="delivered";
	int n2=sendto(sockfd,&buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,clilen);
	return 0;
}