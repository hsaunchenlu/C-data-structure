#include <stdio.h>
#include <stdlib.h>
#define N 5
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct node{
	int data;
	struct node *next;
};

typedef struct node node;

int main(int argc, char *argv[]) {
	int i ;
	node *head,*ptr; 
	head = (node*)malloc(sizeof(node));
	ptr = head;
	int value; 
	
	for (i=0;i<N;i++)
	{
		if ( i == 0){
			scanf("%d",&value);
			head->data = value;
			head->next = NULL;
			
		}else{
			scanf("%d",&value);
			head->data = value;
			head->next = ptr;
			ptr = head;
		}
		
		if (i <=N-2 )
		head = (node*)malloc(sizeof(node));
		
		
	} 
	
	
	for (i=0;i<N;i++){
		if (i==0){
			printf("%d",head->data); //print first of the link list
			ptr = head->next;        //find second address
		}	
		else{
			printf("%d",ptr->data);
			ptr = ptr->next;		//find next address
		}
	}

	return 0;
}
