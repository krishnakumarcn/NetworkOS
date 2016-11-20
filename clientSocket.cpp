//Client side implementation

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<strings.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
using namespace std;

int main(int argc,char* argv[]){
  int sockfd,portno,n;
  
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];
  portno=atoi(argv[1]);

  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0){
    cout<<"ErrorCreationSocketClient";
    return 0;
  }
  server=gethostbyname("localhost");

  bzero( (char*)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
    bcopy(
 	 (char*)server->h_addr,
	 (char*)&serv_addr.sin_addr.s_addr,
	 server->h_length
	 );
  serv_addr.sin_port=htons(portno);

  if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
    cout<<"ErrorConnen=ctingToServer!!";
    return 0;
  }
 while(1){  
    bzero(buffer,255);
    cout<<"You: ";
    fgets(buffer,255,stdin);
    //  if(buffer[0]=='+')break;
    n=write(sockfd,buffer,strlen(buffer));
    if(n<0){
      cout<<"ErrorWritingIntoSocket!!";
      return 0;
    }
    n=read(sockfd,buffer,255);
    if(n<0){
      cout<<"ErrorReadingOnClient!!";
      return 0;
    }
    cout<<"Unknown: "<<buffer<<endl;
  }
  return 0;
}
