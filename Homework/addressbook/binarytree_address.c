#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Btree
{
	char name[80];
	char phone[12];
	struct Btree *left;
	struct Btree *right;
};

typedef struct Btree node;

node *search_node(node *ptr,char value[]){
	node *temp;
	 if (ptr != NULL){
	 	if (strcmp(ptr->name, value)== 0){
	 		return ptr;
		 }else{
		 	temp = search_node(ptr->left,value);
		 	if(temp!=NULL)
		 		return temp;
			temp = search_node(ptr->right,value);
			if(temp != NULL)
				return temp;
		 	
		 }
	 }
	 return NULL;
}

void printInOrder(node *ptr){
	if(ptr == NULL)
		return ;
	printInOrder(ptr->left);
	printf("Name: %s\n",ptr->name);
	printf("Phone: %s\n",ptr->phone);
	puts("============");
	printInOrder(ptr->right);
}

void printInFront(node *ptr){
	if(ptr == NULL)
		return ;
	printf("Name: %s\n",ptr->name);
	printf("Phone: %s\n",ptr->phone);
	puts("============");
	printInFront(ptr->left);
	printInFront(ptr->right);
}

void printInBack(node *ptr){
	if(ptr == NULL)
		return ;
	
	printInBack(ptr->left);
	printInBack(ptr->right);
	printf("Name: %s\n",ptr->name);
	printf("Phone: %s\n",ptr->phone);
	puts("============");
}

node *insert_node(node *root, node data)
{
	node *new_node;
	node *current;
	node *parent;
	
	new_node = (node *)malloc(sizeof(node));
	*new_node = data;
	new_node->left = NULL;
	new_node->right = NULL;
	
	if(root == NULL)
	{
		return new_node;
	}
	else
	{
		current = root;
		while(current != NULL)
		{
			parent = current;
			if(strcmp(current->name,data.name) > 0)
				current = current->left;
			else
				current = current->right;
		}
		if(strcmp(parent->name,data.name) > 0)
			parent->left = new_node;
		else
			parent->right = new_node;
	}
	return root;
}



// 找某值之父節點
node *find_parent(node *ptr, char value[], int *pos)
{
	node *parent;

	parent = ptr;	// 從ptr開始找
	*pos = 0;
	while(ptr != NULL)	
	{
		if(strcmp(ptr->name,value) == 0)	// 找到目標
			return parent;		// 回傳此節點之父節點
		else
		{
			parent = ptr;
			if(strcmp(ptr->name,value) > 0)
			{
				*pos = -1;			// ptr在parent左子樹
				ptr = ptr->left;	// 往左找
			}
			else
			{
				*pos = 1;			// ptr在parent右子樹
				ptr = ptr->right;	// 往右找
			}
		}
	}
	return NULL;	// 找不到
}

// 刪除節點
node *delete_node(node *root, char value[])
{
	node *parent;
	node *ptr;
	node *next;
	int pos;

	parent = find_parent(root, value, &pos);	// 從root開始,找value之父節點
	if(parent != NULL)	// 有找到, 準備刪除
	{
		switch(pos)	// 判斷目前節點再父節點左邊或右邊
		{
			case -1:
				ptr = parent->left;
				break;
			case 1:
				ptr = parent->right;
				break;
			case 0:
				ptr = parent;
				break;
		}
		if(ptr->left == NULL)		// 情況1: 節點沒有左子樹 如果要刪的是根節點
		{
			if(parent == ptr)	// 如果要刪的是根節點
				root = root->right;
			else				// 其他
			{
				if( pos == 1 )
				{
					//要刪除的節點在父節點右方,所以將父節點的右節點指向刪除節點的右節點
					parent->right = ptr->right;
				}
				else
				{
					//要刪除的節點在父節點左方,所以將父節點的左節點指向刪除節點的右節點
					parent->left = ptr->right;
				}
			}
			free(ptr);
		}
		else if(ptr->right == NULL)	// 情況2: 節點沒有右子樹
		{
			if(parent != ptr)
			{
				if( pos == 1 )
				{
					//要刪除的節點在父節點右方,所以將父節點的右節點指向刪除節點的左節點
					parent->right = ptr->left;
				}
				else
				{
					//要刪除的節點在父節點左方,所以將父節點的左節點指向刪除節點的左節點
					parent->left = ptr->left;
				}
			}
			else
				root = root->left;
			free(ptr);
		}
		else						// 情況3: 節點有左右子樹
		{
			parent = ptr;
			next = ptr->left;	// 找取代點next, 從ptr左邊開始找
			if(next->right!=NULL){
				while(next->right != NULL)	// 往左子節點之右子樹找最大值當取代點
				{
				parent = next;		// parent為next之父節點
				next = next->right;
				}
				parent->right = next->left; // 繞過next節點
			}else{
				ptr->left = next->left; // 繞過next節點
			}
			strcpy(ptr->name,next->name);		// 取代!!
			strcpy(ptr->phone,next->phone);
			free(next);	// 刪除next (注意: 不是刪除ptr)
		}
	}
	return root;	// 回傳此樹
}



int main()
{
	node data;
	char op;
	node *root = NULL;
	node *ptr;
	char value[80];
	
	while(1){
		
		puts("i Insert a person");
		puts("l List personal data");
		puts("f Find a person");
		puts("d Delete a person");
		puts("q Quit");
		
		scanf(" %c",&op);
		switch(op){
			case 'i':
				scanf("%s",data.name);
				scanf("%s",data.phone);
				root = insert_node(root,data);
				break;
			
			case 'l':
				printInOrder(root);
				puts("");
				break;
			/*
			case 'm':
				printInFront(root);
				puts("");
				break;
			
			case 'n':
				printInBack(root);
				puts("");
				break;
			*/
			case 'f':
				scanf("%s",value);
				ptr =  search_node(root,value);
				if(ptr!= NULL){
					printf("found: %s\n",ptr->name);
					printf("Phone: %s\n",ptr->phone);
				}else{
					puts("not found\n");
				}
				break;
			case 'd':
				scanf("%s",value);
				ptr =  search_node(root,value);
				if(ptr!=NULL){
					root = delete_node(root,value);
					printf("delete %s ok\n",value);
				}else{
					puts("cannot delete\n");
				}
				break;
			case 'q':
				return 0;
				break;
			default:
				puts("Wrong commend!");
		}
		system("pause");
		system("cls");
	}
	return 0;
}
