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



// ��Y�Ȥ����`�I
node *find_parent(node *ptr, char value[], int *pos)
{
	node *parent;

	parent = ptr;	// �qptr�}�l��
	*pos = 0;
	while(ptr != NULL)	
	{
		if(strcmp(ptr->name,value) == 0)	// ���ؼ�
			return parent;		// �^�Ǧ��`�I�����`�I
		else
		{
			parent = ptr;
			if(strcmp(ptr->name,value) > 0)
			{
				*pos = -1;			// ptr�bparent���l��
				ptr = ptr->left;	// ������
			}
			else
			{
				*pos = 1;			// ptr�bparent�k�l��
				ptr = ptr->right;	// ���k��
			}
		}
	}
	return NULL;	// �䤣��
}

// �R���`�I
node *delete_node(node *root, char value[])
{
	node *parent;
	node *ptr;
	node *next;
	int pos;

	parent = find_parent(root, value, &pos);	// �qroot�}�l,��value�����`�I
	if(parent != NULL)	// �����, �ǳƧR��
	{
		switch(pos)	// �P�_�ثe�`�I�A���`�I����Υk��
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
		if(ptr->left == NULL)		// ���p1: �`�I�S�����l�� �p�G�n�R���O�ڸ`�I
		{
			if(parent == ptr)	// �p�G�n�R���O�ڸ`�I
				root = root->right;
			else				// ��L
			{
				if( pos == 1 )
				{
					//�n�R�����`�I�b���`�I�k��,�ҥH�N���`�I���k�`�I���V�R���`�I���k�`�I
					parent->right = ptr->right;
				}
				else
				{
					//�n�R�����`�I�b���`�I����,�ҥH�N���`�I�����`�I���V�R���`�I���k�`�I
					parent->left = ptr->right;
				}
			}
			free(ptr);
		}
		else if(ptr->right == NULL)	// ���p2: �`�I�S���k�l��
		{
			if(parent != ptr)
			{
				if( pos == 1 )
				{
					//�n�R�����`�I�b���`�I�k��,�ҥH�N���`�I���k�`�I���V�R���`�I�����`�I
					parent->right = ptr->left;
				}
				else
				{
					//�n�R�����`�I�b���`�I����,�ҥH�N���`�I�����`�I���V�R���`�I�����`�I
					parent->left = ptr->left;
				}
			}
			else
				root = root->left;
			free(ptr);
		}
		else						// ���p3: �`�I�����k�l��
		{
			parent = ptr;
			next = ptr->left;	// ����N�Inext, �qptr����}�l��
			if(next->right!=NULL){
				while(next->right != NULL)	// �����l�`�I���k�l���̤j�ȷ���N�I
				{
				parent = next;		// parent��next�����`�I
				next = next->right;
				}
				parent->right = next->left; // ¶�Lnext�`�I
			}else{
				ptr->left = next->left; // ¶�Lnext�`�I
			}
			strcpy(ptr->name,next->name);		// ���N!!
			strcpy(ptr->phone,next->phone);
			free(next);	// �R��next (�`�N: ���O�R��ptr)
		}
	}
	return root;	// �^�Ǧ���
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
