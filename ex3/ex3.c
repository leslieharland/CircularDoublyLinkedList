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
	struct SUBNODE* nextSubNode;
} subNode;

typedef struct NODE
{
	int data;
	struct NODE* previousNode;
	struct NODE* nextNode;
	subNode* subNodeHead;
} node;

// Function prototypes 

void insertNodeNext(int,int,node*); 
void insertNodePrevious(int,int,node*);
void deleteNode(int,node*);
void printList(node*);
void printSubNodes(node*);
void deleteList(node*);
void insertSubNode(int,int,int,node*);
void deleteAllSubNodes(node*);

void collapseSubNodes(int, node*); //TODO 


// Start of main
int main()
{
	int position;
	int instruction;
	int subPosition;
	int value;
	
	// Declaration of the origin Node
	node* originNode = (node*)malloc(sizeof(node));
	originNode->previousNode = originNode;
	originNode->nextNode = originNode;
	originNode->data = 0;
	originNode->subNodeHead = NULL;
	
	
	
	while(scanf("%i%i",&instruction,&position) == 2)
		//scanf() returns an int that corresponds to the number of values scanned. 
	{
		// TODO: You would have to implement input and processing yourself. 
	}
	printList(originNode);
	deleteList(originNode);
	
	printf("Circular List after delete\n");
	printList(originNode);
	
	free(originNode);
	
	return 0;
}


//Function Implementations 

void collapseSubNodes(int position,node* targetNode)
{
	int total = 0;
	if (targetNode != NULL){
		if (targetNode->subNodeHead != NULL){
			node *p = targetNode->subNodeHead;
			while(p){
				p = p->nextNode;
				total += p->data;
			}
		}
	}

	free(targetNode->subNodeHead);
	node *r = (node *)malloc(sizeof(node));
	r->data = total + targetNode->data;
	node *prev = targetNode->previousNode;
	node *next = targetNode->nextNode;
	prev->nextNode = r;
	r->nextNode = next;
}

void insertNodeNext(int position,int value, node* originNode)
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

void insertNodePrevious(int position,int value, node* originNode)
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

void insertSubNode(int position,int subPosition,int value,node* originNode)
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


	if (q->subNodeHead == NULL){
		q-> subNodeHead = (subNode *)
		malloc(sizeof(subNode));
	}else if(subPosition == 0){
		q->subNodeHead = p;

	}else
		insertSubNodeNext(subPosition, value, q->subNodeHead);
}

void deleteAllSubNodes (node* targetNode)
{
	// Use implementation from ex2. 
}

void deleteNode (int position,node* originNode)
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

void deleteList(node* originNode)
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
void printList(node* originNode)
{
	int count = 0;
	printf("Printing clockwise:\n");
	node* iterator = originNode->nextNode;
	printf("[Pos %i:%i]",0,originNode->data);
	// printing subNodes
	printSubNodes(originNode);
	printf("\n   |\n   v\n");
	while(iterator != originNode)
	{
		count++;
		printf("[Pos %i:%i]",count,iterator->data);
		// printing subNodes
		printSubNodes(iterator);
		printf("\n   |\n   v\n");
		iterator = iterator->nextNode;
	}
	printf("[Pos %i:%i]",0,originNode->data);
	// printing subNodes
	printSubNodes(originNode);		
	
	printf("\nPrinting counter-clockwise:\n");
	iterator = originNode->previousNode;
	printf("[Pos %i:%i]",0,originNode->data);
	// printing subNodes
	printSubNodes(originNode);
	printf("\n   |\n   v\n");
	while(iterator!= originNode)
	{
		printf("[Pos %i:%i]",count,iterator->data);
		// printing subNodes
		printSubNodes(iterator);
		printf("\n   |\n   v\n");
		iterator = iterator->previousNode;
		count--;
	}
	printf("[Pos %i:%i]",0,originNode->data);	
	// printing subNodes
	printSubNodes(originNode);
	printf("\n");

	return;
}

void printSubNodes(node* mainNode)
{
	int count = 0;
	subNode* iterator = mainNode->subNodeHead;
	while(iterator != NULL)
	{
		printf("->[subNode pos %i:%i]",count,iterator->data);
		iterator = iterator->nextSubNode;
		count++;
	}
}
