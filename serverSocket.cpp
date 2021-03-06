//serve
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<strings.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

using namespace std;


int main(int argc,char* argv[]){
  int sockfd,newsockfd,portno,n;
  socklen_t clilen;
  
  //for read and write
  char buffer[256];

  /*sockaddr_in contain internet adress, defined under netinet/in.h
  
   struct sockaddr_in{
   short sin_family;//must be AF_INET
   u_short sin_port;
   struct in_addr sin_addr;
   char sin_zero[8];//not used, must be 0
   };

  */

  //serv_addr contain address of server, cli_addr contain address of client
  
  struct sockaddr_in serv_addr,cli_addr;

  if(argc<2){
    cout<<"Error:Input port";
    return 0;
  }

  portno=atoi(argv[1]);

  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd==-1){
    cout<<"Error:socketCreationFailed!";
    return 0;
  }

  ///////////SETTING SERV_ADDR/////////////

  bzero((char*) &serv_addr,sizeof(serv_addr));

  //must be AF_INET
  serv_addr.sin_family=AF_INET;

  serv_addr.sin_port=htons(portno);

  //INADDR_ANY gets the IP address of the machine
  serv_addr.sin_addr.s_addr=INADDR_ANY;

  //binding
  if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) <0){
    cout<<"Error: BindingFailed!!";
    return 0;
  }


  //listen for connections:::::::5-size of backlog queue,nom.of connection that can be wait while the process handling another connection
  listen(sockfd,5);


  //managing the client 
  clilen=sizeof(cli_addr);
  newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
  if(newsockfd<0){
    cout<<"AcceptFailed!!";
    return 0;
  }

  while(1){
    bzero(buffer,256);
    n=read(newsockfd,buffer,255);
    if(n<0){
      cout<<"ErrorReadingFromSocket!";
    }

    cout<<"Unknown: "<<buffer<<endl;
    cout<<"You: ";
    fgets(buffer,255,stdin);
    n=write(newsockfd,buffer,255);
    if(n<0){
      cout<<"ErrorWRITINGfROMsERVER!!";
      return 0;
    }
    
  }


  return 0;
}
  
