#include <iostream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;
void pop(int tower[]){
	int i = 0;
	while (1){
		if(tower[i]!=0){
			i = i+1;
		}
		else{
			tower[i-1] = 0;
			return;
		}
	}	
}

void push(int tower[],int plate){
	int i = 0;
	while(1){
		if(tower[i]!=0){
			i = i+1;
		}else{
			tower[i] = plate;
			return;
		}
	}
}

void hanoi (int n, char from, char mid, char to,int towerA[],int towerB[],int towerC[],int N)
{ 
if(n==0)
return ;
int i;

hanoi(n-1,from, to, mid,towerA,towerB,towerC,N);


cout << "plate " << n << " from " << from << " -> "<< to << endl; 
switch(from){
	case 'A':
		if(to == 'B'){
			pop(towerA);
			push(towerB,n);
		}else{
			pop(towerA);
			push(towerC,n);
		}
		break;
	case 'B':
		if(to == 'A'){
			pop(towerB);
			push(towerA,n);
		}else{
			pop(towerB);
			push(towerC,n);
		}
		break;
	case 'C':
		if(to == 'A'){
			pop(towerC);
			push(towerA,n);
		}else{
			pop(towerC);
			push(towerB,n);
		}
		break;
}

cout << "Tower A : ";
for(i = 0;i<N;i++){
	cout << towerA[i] << " ";
}
cout << endl;

cout << "Tower B : ";
for(i = 0;i<N;i++){
	cout << towerB[i] << " ";
}
cout << endl;

cout << "Tower C : ";
for(i = 0;i<N;i++){
	cout << towerC[i] << " ";
}
cout << endl;
cout << endl;

hanoi(n-1,mid, from, to,towerA,towerB,towerC,N);

}

int main(int argc, char *argv[]) {
	
	int n,N;
	int i;
	int towerA[1000] = {0};
	int towerB[1000] = {0};
	int towerC[1000] = {0};
	//int log[100]={0};
	
	cout << "Input number of plates : " ;
	cin >> n;
	N = n;
	cout << "Tower A : ";
	for(i = 0;i<N;i++){
		push(towerA,N-i);
		
	}
	for(i = 0;i<N;i++){
		cout << towerA[i] << " ";
	}
	cout << endl;
	
	cout << "Tower B : ";
	for(i = 0;i<N;i++){
		
		cout << 0 <<" ";
	}
	cout << endl;
	
	cout << "Tower C : ";
	for(i = 0;i<N;i++){
		cout << 0 <<" ";
	}
	cout << endl;
	cout << endl;
	
	hanoi(n,'A','B','C',towerA,towerB,towerC,N);
	
	
//	while(log[n]!=0){
//		printf("\nplate %d = %d",n+1,log[n]);
//		n+=1;
//	}
	return 0;
}
