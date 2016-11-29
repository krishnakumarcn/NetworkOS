#include<iostream>
#include<sys/statvfs.h>
using namespace std;
int main(){

	struct statvfs vf;
	int n=statvfs("/Works/nos",&vf);
	// man statvfs and substitute x for "vf.x"
	cout<<"FS Block Size: "<<vf.f_namemax<<endl;
}
