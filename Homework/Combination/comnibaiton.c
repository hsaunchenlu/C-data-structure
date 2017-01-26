#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int comb(int,int); 

int main(int argc, char *argv[]) {
	int n , m ;
	scanf("%d" , &n);
	scanf("%d" , &m);
	
	if (n>=m)
	printf("%d",comb(n,m));
	else
	printf("input error");
	
	return 0;
}

int comb(int n,int m)
{
	if(n == m||m == 0)
		return 1;
	else if (n > m)
	{
		return comb(n-1,m)+comb(n-1,m-1);
	} 

}
