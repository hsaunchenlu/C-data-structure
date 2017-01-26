 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void print(int n, char p[][128])
{
	int i;
		for(i=0; i<n; i++)
		{
			printf("%s \n", &p[i][128]);
		}
	printf("\n");
}

int LinearSearch(int n, char p[][128], char value[128])
{
	int i;
	for(i=0; i< n; i++)
		{	
			printf("%d: %s\n",i+1,&p[i][128]);
			if(strcmp(&p[i][128],value)==0)
				{
					return i; // 找到: 傳回資料位置
				}
		}
	return -1; // 找不到: 回傳-1
}

int BinarySearch(int n, char p[][128], char value[128])
{
	int low=0, high=n, mid;
	while(low <= high)
		{
			
			mid = (low + high) / 2;
			printf("%d: %s\n",mid+1,&p[mid][128]);
			if(strcmp(&p[mid][128],value) > 0)
			high = mid -1;
			else if(strcmp(&p[mid][128],value)<0)
			low = mid+1;
			else
			return mid;
		}
	return -1;
}

int main(int argc, char *argv[]) {
	char data[100][128];
	int op,i,j;
	char key[128];
	int n = 0;//current data 
	char value[128];
	int pos;
	
	while(1){
		
		puts("1 insert");
		puts("2 linear search");
		puts("3 binary search");
		puts("4 list");
		puts("5 quit");
		scanf("%d",&op);
		switch (op)
		{
			case 1:
				scanf("%s", &key);
				if (n==0){
					strcpy(&data[0][128],&key);
				}else{
					for(j=n-1; j>=0 && strcmp(&data[j][128],&key)>0; j--) {
					strcpy(&data[j+1][128],&data[j][128]);
					}
					strcpy(&data[j+1][128],&key);//將key插入
				}
				n++;
				break;
			case 2:
				scanf("%s",&value);
				pos = LinearSearch(n,data,value);
				if(pos!=-1){
					printf("found %s\n",&data[pos][128]);
				}else{
					puts("not found");
				}
				break;
			case 3:
				scanf("%d",&value);
				pos = BinarySearch(n,data,value);
				if(pos!=-1){
					printf("found %s\n",&data[pos][128]);
				}else{
					puts("not found");
				}
				break;
			case 4:
				print(n,data);
				break;
			case 5:
				return 0;
				break;
					
		}
		system("pause");
		system("cls");
	}

}
