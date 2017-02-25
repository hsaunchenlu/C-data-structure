#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
class node
{
	public:
	string name;
	string phone;
	private:
	node *left;
	node *right;
	friend class Btree;
};

class Btree{
	public:
		Btree();
		void print();
		void insert(node data);
		void find(string value);
		void remove(string value);
		
	private:
		node *search_node(node *ptr,string value);
		void printInOrder(node *ptr);
		node *insert_node(node data);
		node *find_parent(node *ptr, string value, int *pos);
		void *delete_node(string value);
		
		node *ptr;
		node *root;
};

Btree::Btree(){
	root = NULL;
}

void Btree::print(){
	printInOrder(root);
}

void Btree::insert(node data){
	
	root = insert_node(data);
} 

void Btree::find(string value){
	ptr =  search_node(root,value);
	if(ptr!= NULL){
		cout << "found: " << ptr->name << endl
		     << "Phone: " << ptr->phone<< endl;
	}else{
		cout << "not found" << endl; 
	}
}

void Btree::remove(string value){
	ptr =  search_node(root,value);
	if(ptr!=NULL){
		delete_node(value);
		cout << "delete " << value << " ok" <<endl; 
	}else{
		cout << "cannot delete" <<endl;
	}
}

node *Btree::search_node(node *ptr,string value){
	node *temp;
	 if (ptr != NULL){
	 	if (ptr->name == value){
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

void Btree::printInOrder(node *ptr){
	if(ptr == NULL)
		return ;
	printInOrder(ptr->left);
	cout << "Name: " << ptr->name << endl
		 << "Phone: " << ptr->phone << endl
		 << "============" << endl;
	printInOrder(ptr->right);
}


node *Btree::insert_node(node data)
{
	node *new_node;
	node *current;
	node *parent;
	
	new_node = new node;
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
			if(current->name>data.name)
				current = current->left;
			else
				current = current->right;
		}
		if(parent->name>data.name)
			parent->left = new_node;
		else
			parent->right = new_node;
	}
	return root;
}



// ��Y�Ȥ����`�I
node *Btree::find_parent(node *ptr, string value, int *pos)
{
	node *parent;

	parent = ptr;	// �qptr�}�l��
	*pos = 0;
	while(ptr != NULL)	
	{
		if(ptr->name==value)	// ���ؼ�
			return parent;		// �^�Ǧ��`�I�����`�I
		else
		{
			parent = ptr;
			if(ptr->name>value)
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
void *Btree::delete_node(string value)
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
			ptr->name == next->name;		// ���N!!
			ptr->phone == next->phone;
			free(next);	// �R��next (�`�N: ���O�R��ptr)
		}
	}
}



int main()
{
	Btree Bt;
	node data;
	char op;
	string value;
	
	while(1){
		
		cout << "i Insert a person" << endl
			 << "l List personal data" << endl
			 << "f Find a person" << endl
			 << "d Delete a person" << endl
			 << "q Quit" << endl;
		
		cin >> op;
		switch(op){
			case 'i':
				cin >> data.name;
				cin	>> data.phone;
				Bt.insert(data);
				break;
			
			case 'l':
				Bt.print();
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
				cin >> value;
				Bt.find(value);
				break;
			case 'd':
				cin >> value;
				Bt.remove(value);
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
