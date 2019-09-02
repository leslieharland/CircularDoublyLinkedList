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
} node;

// Function prototypes
void insertNodeNext(int, int, node *);	 // TODO
void insertNodePrevious(int, int, node *); //TODO
void deleteNode(int, node *);			   // TODO
void deleteList(node *);				   // TODO
void insertSubNode(int, int, int, node *); // TODO
void deleteAllSubNodes(node *);			   // Optional TODO: will be useful in ex3.
void insertSubNodeNext(int, int, subNode *);
int getCount(subNode*);

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

//Function Implementations
void insertSubNode(int position, int subPosition, int value, node *originNode)
{
	int i;
	subNode *p, *r;
	node *q;
	q = originNode;
	p = (subNode *)
		malloc(sizeof(subNode));
	p->data = value;
	for (i = 0; i < position; i++)
	{
		q = q->nextNode;
	}

	r = q->subNodeHead ;
	if (q->subNodeHead == NULL)
	{
		p->nextSubNode = r->nextSubNode;
		r->nextSubNode = p;

	}
	else
	{
		int count = getCount(q->subNodeHead);
		if (subPosition < count)
			insertSubNodeNext(5, value, q->subNodeHead);
	}
}

/* Counts no. of nodes in linked list */
int getCount(subNode *head)
{
	int count = 0;		  // Initialize count
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
	// 	int someInt = position;
	// char str[12];
	// sprintf(str, "%d", someInt);
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

		// rebuild old links(watch the order)
		q->nextNode->previousNode = p;
		q->nextNode = p;
	}
	else
	{
		// build new links
		p->nextNode = originNode;
		p->previousNode = originNode->previousNode;

		// rebuild old links(watch the order)
		originNode->previousNode->nextNode = p;
		originNode->previousNode = p;
	}
}

void insertSubNodeNext(int position, int value, subNode *originNode)
{
	subNode *p, *q;
	int i;
	p = (subNode *)
		malloc(sizeof(subNode));
	p->data = value;

	p->nextSubNode = NULL;
	q = originNode;
	for (i = 0; i < position; i++)
	{
		q = q->nextSubNode;
	}

	p->nextSubNode = q->nextSubNode;
	q->nextSubNode = p;
}


void insertNodeNext(int position, int value, node *originNode)
{
	node *p, *q;
	int i;
	p = (node *)
		malloc(sizeof(node));
	p->data = value;

	p->nextNode = NULL;
	q = originNode;
	for (i = 0; i < position; i++)
	{
		q = q->nextNode;
	}
	p->previousNode = originNode;
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
	free(q);
}

void deleteAllSubNodes(node *targetNode)
{
	// Optional TODO
	// it is advised to use a helper function in conjunction with deleteNode().
}

void deleteList(node *originNode)
{
    node *p;
    p = originNode;
    node *q;
    while (p->nextNode != originNode || p != originNode)
    {
        q = (node *)malloc(sizeof(node));
        q = p;
        p = p->nextNode;
        
        q->nextNode = p->nextNode;
        p->previousNode = originNode;
        free(q);
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
