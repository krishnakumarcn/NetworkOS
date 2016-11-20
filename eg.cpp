#include<iostream>
#include<fstream>
using namespace std;
int main(){
	ofstream fp("abc.txt");
	fp<<"hai"<<endl<<"hello";
	fp.close();
	return 0;
}