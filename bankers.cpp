/*
Ex.No.: 07
Bankers Algorithm
Krishnakumar.C.N
Roll No.:34
01/09/2016
*/

#include<iostream>
using namespace std;

int main(){

  int m,n;
  cout<<"Enter the no.of processes: ";
  cin>>m;
  cout<<"Enter the no.of resources: ";
  cin>>n;

  int alloc[m][n],need[m][n],max[m][n],instRes[n],avail[n];

  cout<<"Enter the Allocation Matrix: "<<endl;
  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      cin>>alloc[i][j];

  cout<<"Enter the Max matrix: "<<endl;
  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      cin>>max[i][j];

  cout<<"Enter the Resource Instances: "<<endl;
  for(int j=0;j<n;j++)
      cin>>instRes[j];

  /************Calculate Need***********************/
  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      need[i][j]=max[i][j]-alloc[i][j];

  /*************calculate available*****************/
  for(int i=0;i<n;i++){
    int temp=0;
    for(int j=0;j<m;j++){
      temp+=alloc[j][i];
    }
    avail[i]=instRes[i]-temp;
  }

for(int i=0;i<n;i++)
  cout<<avail[i];

  /**************new request**********************/
  cout<<"Process No. for New Request: ";
  int pno;
  cin>>pno;
  cout<<"Enter the request: ";
  int request[n];
  for(int i=0;i<n;i++){
    cin>>request[i];
    if(request[i]>need[pno][i] || request[i]>avail[i] ){
      cout<<"Request can't be granted!";
      return 0;
    }
  }
  for(int i=0;i<n;i++){
    avail[i]-=request[i];
    alloc[pno][i]+=request[i];
    need[pno][i]-=request[i];
  }

  /***********algorithm**************************/


  bool done[n];
  for(int i=0;i<m;i++)
    done[i]=false;

  int count=0;
  int i=0,cAlloc=0;

  int safe[m];
  while(count!=m){

    if(done[i]==true)
      i++;

    int j=0;
    for(;j<n;j++){
      if(need[i][j]>avail[j])
  break;
    }
    if(j==n){
      done[i]=true;
      safe[count]=i;
      count++;
      cAlloc++;
      for(int k=0;k<n;k++){
  avail[k]=avail[k]-need[i][k]+max[i][k];
      }
    }
    i++;
    if(i==m && cAlloc==0){
      break;
    }
    else if(i==m){
      i=0;
      cAlloc=0;
    }
  
  }
  /********************print*****************************/
  bool flag=false;
  for(int i=0;i<n;i++){
    if(done[i]==false)
      flag=true;
  }
  if(flag)
    cout<<" ** Unsafe **\n";
  else{
    int i=0;
    cout<<"Safe State is: "; 
    for(;i<m-1;i++){
      cout<<"P"<<safe[i]<<"-->";
    }
    cout<<"P"<<safe[i]<<endl;;
  }
  
  return 0; 

}
/*

    OUTPUT
  __________

Enter the no.of processes: 5
Enter the no.of resources: 3
Enter the Allocation Matrix: 
0 1 0
3 0 2
3 0 2
2 1 1
0 0 2
Enter the Max matrix: 
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter the Resource Instances: 
10 5 7
Process No. for New Request: 0
Enter the request: 0 2 0
** Unsafe **


    RESULT
  ___________

The program was executed and output verified.
 */
