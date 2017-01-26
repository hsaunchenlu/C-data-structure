#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void hanoi (int n, char from, char mid, char to,int log[] )
{ // �b�h�ʲ�n�Ӷ�L��
if(n==0)
return ;
// ���N��n-1�Ӷ�L�h�졨������
hanoi(n-1,from, to, mid,log);
// �N�ۤv�h�졨�ؼж�
printf("plate %d from %c -> %c\n",n,from,to);
log[n-1] +=1;

// �A�N��n-1�Ӷ�L�q�������𡨷h�^��
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

