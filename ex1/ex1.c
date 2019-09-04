#include <stdio.h>
#include <stdlib.h>

// stdlib includes malloc() and free()

// define instructions
#define atoa(x) #x
#define PREVIOUS -1
#define NEXT 1
#define DELETE 0

// Node declaration ( Do not edit )
typedef struct NODE
{
	int data;
	struct NODE *previousNode;
	struct NODE *nextNode;
} node;

// Function prototypes
void insertNodeNext(int, int, node *);	 //TODO
void insertNodePrevious(int, int, node *); // TODO
void deleteNode(int, node *);			   // TODO
void deleteList(node *);				   // TODO

void printList(node *); // Implemented for you

// Start of main
int main()
{
	int position;
	int instruction;
	int value;

	// Declaration of the origin Node ( do not edit )
	node *originNode = (node *)malloc(sizeof(node));
	originNode->previousNode = originNode;
	originNode->nextNode = originNode;
	originNode->data = 0;

	// input and processing has been done for you.

	while (scanf("%i%i", &instruction, &position) == 2)
	//scanf() returns an int that corresponds to the number of values scanned.
	{
		if (instruction == DELETE)
		{
			deleteNode(position, originNode);
			//deleteList(originNode);
		}
		else if (instruction == NEXT)
		{
			scanf("%i", &value);
			insertNodeNext(position, value, originNode);
		}
		else if (instruction == PREVIOUS)
		{
			scanf("%i", &value);
			insertNodePrevious(position, value, originNode);
		}
	}
	printList(originNode);
	deleteList(originNode);

	printf("Circular List after delete\n");
	printList(originNode);

	free(originNode);

	return 0;
}

//Function Implementations

void insertNodePrevious(int position, int value, node *originNode)
{
	node *p, *q;
	int i;
	p = (node *)
		malloc(sizeof(node));
	p->data = value;
	p->nextNode = NULL;
	q = originNode;
	if (position > 0)
	{
		for (i = 0; i < position - 1; i++)
		{
			q = q->nextNode;
		}

		p->previousNode = q;
		p->nextNode = q->nextNode;

		q->nextNode->previousNode = p;
		q->nextNode = p;
	}
	else
	{
		p->nextNode = originNode;
		p->previousNode = originNode->previousNode;

		originNode->previousNode->nextNode = p;
		originNode->previousNode = p;
	}
}

void insertNodeNext(int position, int value, node *originNode)
{
	node *p, *q;
	int i;
	p = (node *)
		malloc(sizeof(node));
	p->data = value;

	q = originNode;
	for (i = 0; i < position - 1; i++)
	{
		q = q->nextNode;
	}
	p->previousNode = q;
	p->nextNode = q->nextNode;

	q->nextNode->previousNode = p;
	q->nextNode = p;
}

void deleteNode(int position, node *originNode)
{
	node *p, *q;
	q = originNode;
	int i;
	for (i = 0; i < position; i++)
	{
		p = q;
		q = q->nextNode;
	}

	p->nextNode = q->nextNode;
	p->nextNode->previousNode = p;
	free(q);
}

void deleteList(node *originNode)
{	node *p;
	p = originNode;
	node *q;
	while (p->nextNode != originNode)
	{
		deleteNode(1, originNode);
	}
    
}

// printList has been implemented for you.
// You may study the functions below to help you implement your own functions.
void printList(node *originNode)
{
	int count = 0;

	printf("Printing clockwise:\n");
	node *iterator = originNode->nextNode;
	printf("[Pos %i:%i]", 0, originNode->data);
	printf("\n   |\n   v\n");
	while (iterator != originNode)
	{
		count++;
		printf("[Pos %i:%i]", count, iterator->data);
		printf("\n   |\n   v\n");
		iterator = iterator->nextNode;
	}
	printf("[Pos %i:%i]", 0, originNode->data);

	printf("\nPrinting counter-clockwise:\n");
	iterator = originNode->previousNode;
	printf("[Pos %i:%i]", 0, originNode->data);
	printf("\n   |\n   v\n");
	while (iterator != originNode)
	{
		printf("[Pos %i:%i]", count, iterator->data);
		printf("\n   |\n   v\n");
		iterator = iterator->previousNode;
		count--;
	}
	printf("[Pos %i:%i]\n", 0, originNode->data);

	return;
}
