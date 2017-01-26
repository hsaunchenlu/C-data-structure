#include <stdio.h>
#include <stdlib.h>

#define N 5
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct student
{
	int math;
	int eng;
	int compu;
};
typedef struct student stu;

int main(int argc, char *argv[]) {
	
	stu s[N];
	int sum[5] = {0}; 
	int i,tops;
	int total = 0;
	int top = 0;  
	for(i=0;i<N;i++){
		scanf("%d", &s[i].math);
		scanf("%d", &s[i].eng);
		scanf("%d", &s[i].compu);
	}
	
	for(i=0;i<N;i++){
		printf("student %d\n",i+1);
		printf(" 1: %d\n",s[i].math);
		printf(" 2: %d\n",s[i].eng);
		printf(" 3: %d\n",s[i].compu);
		sum[i] = s[i].math+s[i].eng+s[i].compu; 
		printf(" sum: %d\n",sum[i]);
		printf(" avg: %.2f\n",(double)sum[i]/3); 
		total  += sum[i]; 
	} 
	
	printf("total: %d, avg: %.2f\n",total,(double)total/(3*N)); 
	
	for (i = 0;i<N;i++)
	{
		if  (sum[i]>top){ 
			top = sum[i];
			tops = i+1; 
		}

	} 
	printf("highest avg: student %d: %.2f",tops,(double)top/3); 
	return 0;
}

