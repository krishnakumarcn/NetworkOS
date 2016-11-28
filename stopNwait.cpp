#include <iostream>
#include <random>
#include<unistd.h>
using namespace std;


class Socket{
	string data;
	public:
		int recieve(char c,int seq){
			if(random()%2){
				data=data+c;
				return seq;
			}
			else
				return -1;
		}

		string recieveData(){
			return data;
		}

};

int main(){

	string input;
	Socket sock;
	int ack;

	cout<<"Enter the input: ";
	cin>>input;

	for(int i=0;i<input.length();i++){
		do{
		        sleep(1);
			cout<<"Sending "<<input[i]<<endl;
			ack=sock.recieve(input[i],i);
			sleep(1);
			cout<<"Recieved: ";
			sleep(1);
			if(ack==-1){
				cout<<"Negative!"<<endl;
			}
			else{
				cout<<"Done!!"<<endl;
			}
		}while(ack==-1);
	}
	sleep(1);
	cout<<"Recieved: "<<sock.recieveData()<<endl;
	return 0;
}
