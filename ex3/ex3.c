#include <stdio.h>
#include <stdlib.h>
// stdlib includes malloc() and free()

// define instructions
#define PREVIOUS -1
#define NEXT 1
#define DELETE 0
#define INSERTSUBNODE 2
#define COLLAPSE 3 // New instruction compared to ex2.

// Node declarations

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

void insertNodeNext(int, int, node *);
void insertNodePrevious(int, int, node *);
void deleteNode(int, node *);
void printList(node *);
void printSubNodes(node *);
void deleteList(node *);
void insertSubNode(int, int, int, node *);
void deleteAllSubNodes(node *);

void collapseSubNodes(int, node *); //TODO

// Start of main
int main()
{
	int position;
	int instruction;
	int subPosition;
	int value;

	//function pointers
	typedef void (*insertNodeNextptr)(int, int, node *);
	insertNodeNextptr insertNodeNextCall = insertNodeNext;
	typedef void (*deleteNodeptr)(int, node *);
	deleteNodeptr deleteNodeCall = deleteNode;
	typedef void (*insertSubNodeptr)(int, int, int, node *);
	insertSubNodeptr insertSubNodeCall = insertSubNode;
	typedef void (*insertNodePreviousptr)(int, int, node *);
	insertNodePreviousptr insertNodePreviousCall = insertNodePrevious;
	typedef void (*collapseptr)(int, node *);
	collapseptr collapseCall = collapseSubNodes;

	// Declaration of the origin Node
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
			deleteNodeCall(position, originNode);
		}
		else if (instruction == INSERTSUBNODE)
		{
			scanf("%i%i", &subPosition, &value);
			insertSubNodeCall(position, subPosition, value, originNode);
		}
		else if (instruction == NEXT)
		{
			scanf("%i", &value);
			insertNodeNextCall(position, value, originNode);
		}
		else if (instruction == PREVIOUS)
		{
			scanf("%i", &value);
			insertNodePreviousCall(position, value, originNode);
		}
		else if (instruction == COLLAPSE)
		{
			scanf("%i", &value);
			collapseCall(position, originNode);
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

void collapseSubNodes(int position, node *targetNode)
{
	node *p = targetNode;
	for (int i = 0; i < position ; i++)
	{

		p = p->nextNode;
	}
	int total = 0;

	subNode *s = p->subNodeHead;
	while (s != NULL)
	{
		total += s->data;
		s = s->nextSubNode;
	
		
		
		
	}
	

	p->data = p->data + total;

	deleteAllSubNodes(p);
}

void insertNodeNext(int position, int value, node *originNode)
{
	node *p, *q;
	int i;
	p = (node *)malloc(sizeof(node));
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

void insertNodePrevious(int position, int value, node *originNode)
{
	node *p, *q;
	int i;
	p = (node *)malloc(sizeof(node));
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
	subNode *temp;
	while (targetNode->subNodeHead != NULL)
	{
		temp = targetNode->subNodeHead;
		targetNode->subNodeHead = targetNode->subNodeHead->nextSubNode;
		free(temp);
		//deleteSubNode(1, targetNode->subNodeHead);
	}
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
	deleteAllSubNodes(q);
	p->nextNode = q->nextNode;
	p->nextNode->previousNode = p;
	free(q);
}
void deleteList(node *originNode)
{
	node *p = originNode;
	while (p->nextNode != originNode)
	{

		deleteNode(1, originNode);
	}
	deleteAllSubNodes(originNode);
}

//Print list has been implemented for you.
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
