/*#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
*/

#include <iostream>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(){

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(sockfd,(struct sockaddr*) &servaddr, sizeof(servaddr))<0){
		cout<<"errorOnBinding!";
		return -1;
	}
	if(listen(sockfd,5)<0){
		cout<<"errorOnListen!";
		return -1;
	}
	struct sockaddr cliaddr;
	socklen_t clilen=sizeof(cliaddr);

	int newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr, &clilen);

	char buffer[256];
	ofstream fp("gotFile.txt");
	
	while(1){
		//bzero(buffer,256);
		read(newsockfd,buffer,256);
		if(buffer[0]=='\0')
			break;
		fp<<buffer;
		fp<<endl<<endl;
	}
	fp.close();
	cout<<"\nFile Recieved";
	system("cat gotFile.txt");
	return 0;
}