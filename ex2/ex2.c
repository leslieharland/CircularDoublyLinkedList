#include <stdio.h>
#include <stdlib.h>
// stdlib includes malloc() and free()

// define instructions
#define PREVIOUS -1
#define NEXT 1
#define DELETE 0
#define INSERTSUBNODE 2 // New instruction compared to ex1.

// Node and SubNode declarations ( Do not Edit )
typedef struct SUBNODE
{
	int data;
	struct SUBNODE *nextSubNode;
} subNode;

typedef struct NODE
{
	int data;
	struct NODE *previousNode;
	struct NODE *nextNode;
	subNode *subNodeHead;
	int index;
} node;

// Function prototypes
void insertNodeNext(int, int, node *);	 // TODO
void insertNodePrevious(int, int, node *); //TODO
void deleteNode(int, node *);			   // TODO
void deleteList(node *);				   // TODO
void insertSubNode(int, int, int, node *); // TODO
void deleteAllSubNodes(node *);			   // Optional TODO: will be useful in ex3.
void insertSubNodeNext(int, int, subNode *);
int getCount(subNode *);

void printList(node *);		// Implemented for you
void printSubNodes(node *); // Implemented for you :Helper function for print list

// Start of main
int main()
{
	int position;
	int instruction;
	int subPosition;
	int value;

	// Declaration of the origin Node ( do not edit )
	node *originNode = (node *)malloc(sizeof(node));
	originNode->previousNode = originNode;
	originNode->nextNode = originNode;
	originNode->data = 0;
	originNode->subNodeHead = NULL;

	// input and processing has been done for you
	while (scanf("%i%i", &instruction, &position) == 2)
	//scanf() returns an int that corresponds to the number of values scanned.
	{
		if (instruction == DELETE)
		{
			deleteNode(position, originNode);
		}
		else if (instruction == INSERTSUBNODE)
		{
			scanf("%i%i", &subPosition, &value);
			insertSubNode(position, subPosition, value, originNode);
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

node *getNode(int position, node *originNode)
{
	node *p = originNode;
	if (position == 0)
		return originNode;
	for (int i = 0; i < position; i++)
	{
		if (p->nextNode == NULL)
			return p;
		p = p->nextNode;
	}

	return p;
}
//Function Implementations
void insertSubNode(int position, int subPosition, int value, node *originNode)
{
	int i;
	subNode *p, *r;
	node *q = getNode(position, originNode);


	if (q->subNodeHead == NULL || subPosition == 0)
	{
		p = q->subNodeHead;
		subNode *temp = (subNode *)
			malloc(sizeof(subNode));
		temp->data = value;
		temp->nextSubNode = q->subNodeHead;
		q->subNodeHead = temp;
	}
	else
	{
		subNode *temp = (subNode *)
			malloc(sizeof(subNode));
		temp->data = value;
		p = q->subNodeHead;
		int added = 0;

		for (int i = 0; i < subPosition - 1; i++)
		{
			p = p->nextSubNode;
			}
		if (added == 0)
		{

			temp->nextSubNode = p->nextSubNode;
			p->nextSubNode = temp;
		}
	}
}

/* Counts no. of nodes in linked list */
int getCount(subNode *head)
{
	int count = 0;			 // Initialize count
	subNode *current = head; // Initialize current
	while (current != NULL)
	{
		count++;
		current = current->nextSubNode;
	}
	return count;
}

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
	for (i = 0; i < position; i++)
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
	//deleteAllSubNodes(q);
	p->nextNode = q->nextNode;
	p->nextNode->previousNode = p;
	free(q);
}

void deleteSubNode(int position, subNode *originNode)
{
	subNode *p = NULL;
	subNode *q = originNode;
	int i;
	for (i = 0; i < position; i++)
	{
		
		q = q->nextSubNode;
	}
	p = q->nextSubNode;
	q->nextSubNode = p->nextSubNode;

	free(p);
}

void deleteAllSubNodes(node *targetNode)
{
	subNode *p = targetNode->subNodeHead;
	while (p->nextSubNode != NULL)
	{
			
		deleteSubNode(1, targetNode->subNodeHead);
	}
}

void deleteList(node *originNode)
{	
	node *p = originNode;
	while (p->nextNode != originNode)
	{

		deleteNode(1, originNode);
	}
    
}

//Print list has been implemented for you.
// You may study the functions below to help you implement your own functions.
void printList(node *originNode)
{
	int count = 0;
	printf("Printing clockwise:\n");
	node *iterator = originNode->nextNode;
	printf("[Pos %i:%i]", 0, originNode->data);
	// printing subNodes
	printSubNodes(originNode);
	printf("\n   |\n   v\n");
	while (iterator != originNode)
	{
		count++;
		printf("[Pos %i:%i]", count, iterator->data);
		// printing subNodes
		printSubNodes(iterator);
		printf("\n   |\n   v\n");
		iterator = iterator->nextNode;
	}
	printf("[Pos %i:%i]", 0, originNode->data);
	// printing subNodes
	printSubNodes(originNode);

	printf("\nPrinting counter-clockwise:\n");
	iterator = originNode->previousNode;
	printf("[Pos %i:%i]", 0, originNode->data);
	// printing subNodes
	printSubNodes(originNode);
	printf("\n   |\n   v\n");
	while (iterator != originNode)
	{
		printf("[Pos %i:%i]", count, iterator->data);
		// printing subNodes
		printSubNodes(iterator);
		printf("\n   |\n   v\n");
		iterator = iterator->previousNode;
		count--;
	}
	printf("[Pos %i:%i]", 0, originNode->data);
	// printing subNodes
	printSubNodes(originNode);
	printf("\n");

	return;
}

void printSubNodes(node *mainNode)
{
	int count = 0;
	subNode *iterator = mainNode->subNodeHead;
	while (iterator != NULL)
	{
		printf("->[subNode pos %i:%i]", count, iterator->data);
		iterator = iterator->nextSubNode;
		count++;
	}
}
