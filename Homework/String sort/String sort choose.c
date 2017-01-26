#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void swap(char*a, char*b)
{
char temp[80];
strcpy(temp,a);
strcpy(a,b);
strcpy(b,temp);

}

void print(int n, char p[][80])
{
int i;
for(i=0; i<n; i++)
{
printf("%s ", &p[i][80]);
}
printf("\n");
}

int bsort(int n,char data[][80])
{
//int data[5] = {34,12,5,66,1}; // 欲排序的資料
int i, j;
//int n=5;

for(i=n; i>1; i--)
{
for(j=0; j<i-1; j++)
{
	
if(strcmp(&data[j+1][80],&data[j][80]) < 0)
{

swap(&data[j+1][80], &data[j][80]);

}


}
print(n,data);
}
//print(n, data);
return 0;
}

int ssort(int n,char data[][80])
{
//int data[5] = {34,12,5,66,1}; // 欲排序的資料
int i, j, pos; // pos: 紀錄目前最小值位置
//int n=5;
for(i=0; i<n-1; i++)
{
	pos = i;
	for(j=i+1; j<n; j++) // 找出最小值
	{
		if(strcmp(&data[j][80],&data[pos][80]) < 0)
		pos = j;
	}
	// 把最小值跟第i個做交換
	swap(&data[i][80], &data[pos][80]);
	print(n,data);
}
//print(n, data);
return 0;
}

int isort(int n,char data[][80])
{
//int data[5] = {34,12,5,66,1}; // 欲排序的資料
int i, j;
char *key[80]; // 紀錄要被插入的值
//int n=5;
for( i=1; i<n; i++)
{
strcpy(key,&data[i][80]);

for(j=i-1; j>=0 && strcmp(&data[j][80],key)>0; j--)
{
	strcpy(&data[j+1][80],&data[j][80]);

}
strcpy(&data[j+1][80],key); //將key插入
print(n,data);
}
//print(n, data);
return 0;
}


int main(int argc, char *argv[]) {
	char data[N][80];
	int op;
	int i;
	puts("Input six string(Less than 80 chars)");
	for(i = 0;i<N;i++){
		scanf("%s",&data[i][80]);
	}
	
	puts("Choose a sort method\n1 : Bubble sort.\n2 : Select sort.\n3 : Insert sort.");
	scanf("%d",&op);
	switch (op)
	{
		case 1:
			bsort(N,&data);
			break;
		case 2:
			ssort(N,data);
			break;
		case 3:
			isort(N,data);
			break;
	}
	print(N,data);
	return 0;
}
