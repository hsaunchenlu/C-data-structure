#include <stdio.h>
#include <stdlib.h>

// ���|���c���ŧi
struct stack_node 
{
	int x;
	int y;
	struct stack_node *next;
};
typedef struct stack_node node;

node *path = NULL;

// ���|��ƪ��s�J
node *push(node *stack, int x, int y)
{
     
	node *new_node;	
	new_node = (node *)malloc(sizeof(node));	
	
	//�P�_�t�m�O�_���\
	
	if(new_node==NULL) 
	{
		printf("�O����t�m����!\n");
		//exit(0);
    }
	
	new_node->x = x;
	new_node->y = y;
	new_node->next = stack;
	stack = new_node;
	
	return stack;
	
}


//���|��ƪ����X
node *pop(node *stack, int *x, int *y)
{
	node *top;

	if( stack != NULL ) //�P�_���|�O�_���Ū�
	{
		top = stack;
		stack = stack->next;
		*x = top->x;
		*y = top->y;
		free(top);
	}
	else 
	{
		*x = -1;
		*y = -1;
	}
	return stack;
}


void walk(int maze[][10], int x, int y)
{
	while(1)
	{
		if(x==1 && y==1) // �O�_���X�f
		{
			path = push(path, x, y);
			maze[y][x] = 2; // �Х̫ܳ�@�I
			break;
		}
		maze[y][x] = 2; // �Хܬ����L����
		if( maze[y-1][x] <= 0 ) // ���W�訫
		{
			path = push(path, x, y);
			y--;
		}
		else if( maze[y+1][x] <= 0 ) // ���U�訫
		{
			path = push(path, x, y);
			y++;
		}
		else if( maze[y][x-1] <= 0 ) // �����訫
		{
			path = push(path, x, y);
			x--;
		}
		else if( maze[y][x+1] <= 0 ) // ���k�訫
		{
			path = push(path, x, y);
			x++;
		}
		else // �L���i�� => �^��
		{
			maze[y][x] = 3;
			path = pop(path, &x, &y); // �h�^�@�B
		}
	}
}

void reverse(node *ptr){
	if (ptr->next == NULL){
		printf("\n[ %d, %d]",ptr->x,ptr->y);
		return;
	}else{
		reverse(ptr->next);
		printf("\n[ %d, %d]",ptr->x,ptr->y);
	}
	
	
}
// �D�{��
int main()
{
	// �ŧi
	int i, j;
	
	// ��J
	int maze[15][10] = // x=10, y=15
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 1, 0, 1, 0, 0, 1,
		1, 1, 1, 0, 1, 1, 1, 0, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 0, 1,
		1, 1, 0, 0, 1, 0, 1, 0, 1, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 0, 1, 0, 1, 0, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	// �p��
	walk(maze, 1, 13);

	// ��X
	printf("�g�c���|��:\n");
	for(i=0; i<15; i++)
	{
		for(j=0; j<10; j++)
			printf("%d ", maze[i][j]);
		printf("\n");
	}
	node *ptr = path;
	
	reverse(ptr);
	/*
	while(ptr!= NULL){
		printf("[ %d, %d]\n",ptr->x,ptr->y);
		ptr = ptr->next;
	}	*/

	// ����
	system("pause");
	return 0;
}
