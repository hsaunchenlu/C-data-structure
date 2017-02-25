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
	int Index;
	
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
		void remove(int index);
		
	private:
		node *search_node(node *ptr,string value);
		void printInOrder(node *ptr);
		node *insert_node(node data);
		node *find_parent(node *ptr, string value, int *pos);
		node *find_by_index(node *ptr,int index);
		void *delete_node(string value);
		
		int Start;
		node *ptr;
		node *root;
};


Btree::Btree(){
	root = NULL;
	Start = 1;
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
			 << "Index: " << ptr->Index << endl
		     << "Phone: " << ptr->phone<< endl;
	}else{
		cout << "not found" << endl; 
	}
}

void Btree::remove(int index){
	string value;
	ptr =  find_by_index(root,index);
	
	
	if(ptr!=NULL){
		value = ptr->name;
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
	cout << "Index: " << ptr->Index << endl
		 << "Name: " << ptr->name << endl
		 << "Phone: " << ptr->phone << endl
		 << "============" << endl;
	printInOrder(ptr->right);
}

node *Btree::find_by_index(node *ptr,int index){
	node *temp;
	 if (ptr != NULL){
	 	if (ptr->Index == index){
	 		return ptr;
		 }else{
		 	temp = find_by_index(ptr->left,index);
		 	if(temp!=NULL)
		 		return temp;
			temp = find_by_index(ptr->right,index);
			if(temp != NULL)
				return temp;
		 	
		 }
	 }
	 return NULL;
}

node *Btree::insert_node(node data)
{
	node *new_node;
	node *current;
	node *parent;
	
	new_node = new node;
	*new_node = data;
	new_node->Index = Start;
	Start = Start+1;
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



// 找某值之父節點
node *Btree::find_parent(node *ptr, string value, int *pos)
{
	node *parent;

	parent = ptr;	// 從ptr開始找
	*pos = 0;
	while(ptr != NULL)	
	{
		if(ptr->name==value)	// 找到目標
			return parent;		// 回傳此節點之父節點
		else
		{
			parent = ptr;
			if(ptr->name>value)
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
void *Btree::delete_node(string value)
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
			ptr->name == next->name;		// 取代!!
			ptr->phone == next->phone;
			free(next);	// 刪除next (注意: 不是刪除ptr)
		}
	}
}



int main()
{
	Btree Bt;
	node data;
	char op;
	string value;
	int index;

	
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
				cin >> index;
				Bt.remove(index);
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
