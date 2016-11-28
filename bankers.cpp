#include<iostream>
#include<stdlib.h>
using namespace std;

class Banker{
	int m,n;
	int avail[20],alloc[20][20],max[20][20];
	int need[20][20],work[20],req[20];
	int pno;
public:
	void read(){
		cout<<"Enter m, n : ";
		cin>>m>>n;
	/********MAX***********/
		cout<<"Enter the Max:\n";
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				cin>>max[i][j];
	/********Alloc***********/
		cout<<"Enter the Allocation:\n";
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				cin>>alloc[i][j];
	/********Available***********/
		cout<<"Enter the Available:";
		for(int i=0;i<n;i++){
			cin>>avail[i];
		}
	}

	void calcNeed(){

		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				need[i][j]=max[i][j]-alloc[i][j];
			}
		}
	}

	bool request(){		
		cout<<"\n-----Request-----\n";
		cout<<"Enter the process no.: ";
		cin>>pno;
		cout<<"Enter the request: ";
		for(int i=0;i<n;i++){
			cin>>req[i];
		}
		//must be less than need and available
		for(int i=0;i<n;i++){
			if(req[i]>need[pno][i]||req[i]>avail[i]){
				cout<<"Request Cannot be satisfied!";
				return false;
			}
		}
		//do the calcs!!
		for(int i=0;i<n;i++){
			avail[i]=avail[i]-req[i];
			need[pno][i]-=req[i];
			alloc[pno][i]+=req[i];
		}
		return true;
	}

	void isSafe(){

		for(int i=0;i<n;i++)
			work[i]=avail[i];

		bool finish[m];
		for(int i=0;i<m;i++)
			finish[i]=false;


		int i=0;
		int count=0;
		while(1){

			if(finish[i]==true){
				int j=0;
				for(;j<m;j++)
					if(finish[j]==false)
						break;
				if(j==m)
					break;
				else{
					i=j;
				}

			}
			int j=0;
			for(;j<n;j++){
				if(need[i][j]>work[j])
					break;
			}
			if(j==n){
				finish[i]=true;
				cout<<"p"<<i<<"  ";
				for(int k=0;k<n;k++)
					work[k]=work[k]+alloc[i][k];
			}
			i++;
		
			if(i==m){
				//count for determining is unsafe??
				count++;
				if(count==m){
					cout<<"Unsafe";
					break;
				}
				i=0;
			}
		}


	}

};
int main(){
	
	Banker banker;
	banker.read();
	banker.calcNeed();
	char choice;
	do{
		if(banker.request()){
			banker.isSafe();
		}
		cout<<"\nContinue (Y/N)  :";
		cin>>choice;
	}while(choice=='Y'||choice=='y');
	


	// SAFETY ALGORITHM
	return 0;
}
