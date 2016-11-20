
#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;

void* worker(void* i){
  long tid=(long)i;
  int x=0;
  srand(tid);
  do{
    int r=rand()%5+1;
    x+=r;
    cout<<"tid "<<tid<<" Value: "<<x<<endl;
  }while(x<40);
  cout<<"TID :"<<tid<<"Won the race";
  exit(0);
  pthread_exit(NULL);
  
}
int main(){
  int rc;
  pthread_t threads[7];
  for(int i=0;i<7;i++){
    rc=pthread_create(&threads[i],NULL,worker,(void*)i);
  }
  pthread_exit(NULL);
  return 0;
}
    
