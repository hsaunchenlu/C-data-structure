#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CARD 52
#define NUMBER 13
#define SUIT 4
#define PEOPLE 4

#define MAX_SIZE 52

// ���|���c���ŧi
int stack[MAX_SIZE];
int top=-1;


// ���|��ƪ��s�J
int push(int value)
{
	if( top == MAX_SIZE-1 )
	{
		return -1;
	}
	top++;
	stack[top] = value;
	return 1;
}

//���|��ƪ����X
int pop()
{
	int temp;

	if( top == -1 ) //�P�_���|�O�_���Ū�
	{
		return -1;
	}
	temp = stack[top];
	stack[top] = 0;
	top--;
	return temp;
}

void InsertionSort(int n, int *data)
{
	int i, j, key;
    for( i=1; i<n; i++) 
    {
        key=data[i];
        for(j=i-1; j>=0 && data[j]>key; j--)
        {
            data[j+1] = data[j];
        }
        data[j+1] = key;  //�Nkey���J
    }
}

void reshuffle()
{
	int pos;
	int i;
	int card[CARD]={0};
	srand(time(NULL));
	i=0;
	int add = 0;
	while(i!=CARD)
	{
		pos = rand()%CARD;
		if(card[pos]==0)
		{
			push(pos);
			card[pos]=1;
			i++;
		}else{
			push(CARD-(i-1));
			card[CARD-(i-1)]=1;
			i++;
		}
		add++;
	}
	printf("random pick %d times \n",add);
}

void displayCard(int n, int *card)
{
	int i;
	int style[4] = {5,4,3,6};	
	printf("Player%d:\n", n+1);
	for(i=0; i<CARD/PEOPLE; i++)
	{
		printf("[%c %2d] ", style[card[i]/NUMBER], card[i]%NUMBER+1);
	}
	printf("\n");
}

// �D�{��
int main()
{
	// �ŧi
	int i, j;
	int player[PEOPLE][CARD/PEOPLE];
	
	// �~�P
	reshuffle();
	
	// �o�P
	for(i=0; i<CARD/PEOPLE; i++)
	{
		for(j=0; j<PEOPLE; j++)
		{
			player[j][i] = pop();
		}
	}

	// �ݵP
	for(i=0; i<PEOPLE; i++)
		displayCard(i, player[i]);
	printf("\n");

	// �Ƨ�
	for(i=0; i<PEOPLE; i++)
	{
		InsertionSort(CARD/PEOPLE, player[i]);
		displayCard(i, player[i]);
	}
	system("pause");
	return 0;
}
