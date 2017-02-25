#include <cstdio>
#include <iostream>
#include <iomanip>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
class node{
	private:
	int data;
	string ch;
	node *next;
	node *pre;
	friend class Linklist;
};

class Linklist{
	public:
 	Linklist();
	void insert(int value,string Ifprime);
	void PrintInOrder();
	void PrintInReverse();
		
	private:
	void insert_node(node *ptr,int value,string Ifprime);
	node *getnode();
	node *head;
	node *tail;
};

Linklist::Linklist(){
	head = NULL;
	tail = NULL;
}

node *Linklist::getnode(){
	node *p;
	p = new node;
	if (p==NULL){
		cout << "Memery not enough" <<endl;
	}
	return (p); 
}

void Linklist::insert_node(node *ptr,int value,string Ifprime){
	node *newnode;
	newnode = getnode();
	newnode->data = value;
	newnode->ch = Ifprime;
	newnode->next = NULL;
	newnode->pre = NULL;
	if(ptr == NULL){
		newnode->next = head;
		head = newnode;
	}else{
		if (ptr->next ==NULL){
			ptr->next = newnode;
			newnode->pre = ptr;
			tail = newnode;
		}else{
			newnode->pre = ptr;
			ptr-> next->pre = newnode;
			newnode->next = ptr->next;
			ptr->next = newnode;
			
		}
	} 
	
}

void Linklist::insert(int value,string Ifprime){
	node *ptr;
	ptr = head;
	if (ptr == NULL){
		insert_node(NULL,value,Ifprime);
		tail = head;
	}else{
		while(ptr->next!=NULL)
			ptr = ptr->next;
		insert_node(ptr,value,Ifprime);
	}
}

void Linklist::PrintInOrder(){
	node *q;
	q = head;
	while(q!=NULL){
		cout << setw(10) <<q->data << " | " << q->ch << endl;
		q = q->next;
	}
	cout << endl;
}

void Linklist::PrintInReverse(){
	node *q;
	q = tail;
	while(q != NULL){
		cout << setw(10) << q->data << " | " << q->ch << endl;
		q = q->pre;
	}
	cout << endl; 
}



int main(int argc, char** argv) {
	int n;
	int i;
	int j;
	int flag = 0;
	string Ifprime;
	char op;
	Linklist lst;
	cout << "Input a integer, I can find its factors and judge if they are prime." << endl;
	
	cin >> n;
	for(i = 1;i<=n;i++){
		if(n%i == 0){
			flag = 0;
			for (j = 2;j*j<=i;j++){
				if (i%j ==0){
					flag = 1;
				}
			}
			if (flag == 1){
				Ifprime = "Composite";
			}else{
				Ifprime = "Prime"; 
			}
			lst.insert(i,Ifprime);
	   }
	}
		
	
	while(1){
		cout << "Your number is "<< n << endl;
		
		cout << "f Print its factors in order" << endl
			 << "b Print its factors in reverse order" << endl
			 << "q quit" << endl;
		cin >> op;
		cout << endl;
		switch(op){
			case 'f':
					lst.PrintInOrder();
				break;
			case 'b':
					lst.PrintInReverse();
				break;
			case 'q':
				return 0;
				break;
			default:
				cout << "Wrong Commend!" <<endl;
		}
		cout << endl;
		system("pause");
		system("cls");
	}
	
	
	
	return 0;
}
