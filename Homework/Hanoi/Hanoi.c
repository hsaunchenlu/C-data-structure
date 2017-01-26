#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void hanoi (int n, char from, char mid, char to,int log[] )
{ // 在搬動第n個圓盤時
if(n==0)
return ;
// 先將第n-1個圓盤搬到”中間塔”
hanoi(n-1,from, to, mid,log);
// 將自己搬到”目標塔”
printf("plate %d from %c -> %c\n",n,from,to);
log[n-1] +=1;

// 再將第n-1個圓盤從”中間塔”搬回來
hanoi(n-1,mid, from, to,log);
return (log);
}

int main(int argc, char *argv[]) {
	int n;
	int log[100]={0};
	scanf("%d",&n);
	hanoi(n,'A','B','C',log);
	n=0;
	//printf("\n");
	while(log[n]!=0){
		printf("\nplate %d = %d",n+1,log[n]);
		n+=1;
	}
	return 0;
}

