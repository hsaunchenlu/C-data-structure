#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct node{
	char name[80];
	char phone[12];
	char email[80];
	struct node *next;
};

typedef struct node node;
node *getnode(){
	node *p;
	p = (node*)malloc(sizeof(node));
	
	if (p == NULL){
		puts("Memory is not enough");
		exit(1);
	}
	return(p);
}

void freenode(node *p){
	free(p);
}


node *insert_node(node *head,node* ptr,node data){
	node *new_node;
	new_node = getnode();
	*new_node = data;
	new_node->next = NULL;
	if (ptr == NULL){
		new_node->next = head;
		head = new_node;
		
	}else{
		if (ptr->next == NULL){
			ptr->next = new_node;
		}else{
			new_node->next = ptr->next;
			ptr->next = new_node;
		}
	}
	return(head);
}

node *find_node(node *head,char people[80]){
	node *ptr;
	ptr = head;
	char *a[80],*b[80];
	int c;
	*b = people;
	while(ptr != NULL){
		*a = ptr->name; 
		c = strcmp(*a,*b);
		if (c == 0){
			return(ptr);
		}	
		ptr=ptr->next;
	}
	return(ptr);
}

node *delete_node(node *head,node *ptr){
	node *previous;
	if (ptr == head){
		head = head->next;
	}else{
		previous = head;
		while(previous->next != ptr){
			previous = previous->next;
		}
		if (ptr->next == NULL){
			previous->next = NULL;
		}else{
			previous->next = ptr->next;
		}
	}
	freenode(ptr);
	
	return(head);
}

int main(int argc, char *argv[]) {
	node *head, *ptr;
	node data;
	char op;
	int pos;
	char choose[80];
	head = NULL;
	ptr = head;
	
	
	
	while(1){
		puts("i: Insert the information of a member");
		puts("d: Delete the information of a member");
		puts("f: Find the information of a member");
		puts("l: List the member information");
		puts("q: Quit");
			
		scanf(" %c", &op);
		
		switch(op){
			case 'i':
				puts("name");
				scanf("%s",&data.name);
				puts("phone");
				scanf("%s",&data.phone);
				puts("email");
				scanf("%s",&data.email);
		
				if(head == NULL){
					head = insert_node(head,NULL,data);
				}else{
					ptr = head;
					while(ptr->next!=NULL && ptr->next)
					ptr = ptr->next;
					head = insert_node(head,ptr,data);
				}		
				
				break;
				
			case 'l':
				ptr = head;
				while(ptr != NULL){
					printf("name: %s\n",ptr->name);
					printf("phone: %s\n",ptr->phone);
					printf("email %s\n",ptr->email);
					puts("=============");
					ptr = ptr->next;
				}
				break;
				
			case 'd':
				
				puts("name");
				scanf("%s",&choose);
				ptr = find_node(head,choose);
				
				if (ptr == NULL){
					puts("Not found the member");
				}else{
					puts("Delete ok!");
					head = delete_node(head,ptr);
			   }
				break;
			case 'f':
				puts("name");
				scanf("%s",&choose);
				ptr = find_node(head,choose);
				
				if(ptr == NULL)
					puts("Not found");
				else{
					printf("Found the member! \nname : %s \nphone : %s \nemail : %s\n", ptr->name,ptr->phone,ptr->email);
				}
				break;
			case 'q':
				ptr = head;
				while(ptr!=NULL){
					freenode(ptr);
					ptr=ptr->next;
				}
				return 0;
				break;
		}
		system("pause");
		system("cls");
	}
	
	
	return 0;
}
