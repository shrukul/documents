#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	char name[15];
	int type;
	int lineno[15];
	int cnt;
	struct node *nextNode;
};

typedef struct node node;

node *nodeList = (node *)0;

struct node * getNode(char *name)
{
	node *ptr;
	for(ptr = nodeList;ptr != (node *)0;ptr = ptr->nextNode)
		if(strcmp(ptr->name,name)==0)
			return ptr;
	return (node *)0;
}

void insert(char *name, int type, int lineno)
{
	node *ptr;
	ptr = getNode(name);
	printf("heynow");
	if(ptr == (node *)0)
	{
		ptr = (node *) malloc(sizeof(node));
		ptr -> cnt = 0;
		strcpy(ptr->name,name);
		ptr -> type = 0;
		ptr -> lineno[(ptr->cnt)++] = lineno;
		ptr -> nextNode = nodeList;
		nodeList = ptr;
		printf("nowow");
	}
	else{
		ptr -> lineno[(ptr->cnt)++] = lineno;
	}
}

void setType(char *name, int type)
 {
 	struct node *ptr = getNode(name);
 	ptr -> type = type;
 }

 void symDump()
 {
 	node *ptr = nodeList;
 	int cnt;
 	for(;ptr!=(node *)0;ptr=ptr->nextNode){
 		printf("name - %s type - %d ",ptr->name,ptr->type);
 		for(cnt=0;cnt<ptr->cnt;cnt++)
 			printf("%d ",ptr->lineno[cnt]);
 		printf("\n");
 	}
 }