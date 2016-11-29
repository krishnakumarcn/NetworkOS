#include <iostream>
#include <queue>
#include <map>
#include <random>
#include <unistd.h>
using namespace std;


class Socket{
	map<int,char> data;
public:
	int recieve(char c,int seq){
		if(random()%2){
			data[seq]=c;
			return seq;
		}
		else{
			return -1;
		}
	}

	string recieveData(){
		string ret="";
		for(auto i=data.begin();i!=data.end();i++){
			ret+= i->second;
		}
		return ret;
	}
  
};
int main(){

  string input;
  cout<<"Enter the input: ";
  cin>>input;
  int ack;
  Socket sock;

  queue< pair<int,char> > data;
  for(int i=0;i<input.length();i++){
  	data.push( pair<int,char>(i,input[i]) );
  }
  while(!data.empty()){
  	pair<int,char> d=data.front();
  	cout<<"Sending: "<<d.second<<" :"<<d.first <<endl;
  	data.pop();
  	ack=sock.recieve(d.second,d.first);
  	if(ack==-1){
  		cout<<"No ACK !!   :  -1 \n";
  		data.push(d);
  	}
  	else{
  		cout<<"Recieved ACK:  "<<ack<<endl;

  	}
  }
  cout<<"Recieved: "<<sock.recieveData()<<endl;
  
  return 0;
}
