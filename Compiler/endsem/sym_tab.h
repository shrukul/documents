#include <stdio.h>
#include <string.h>

struct node {
	char name[15];
	int type;
	int val;
	int line[15];
	int cnt;
	int isfunc;
	int level;
	struct node *nextNode;
};

typedef struct node node;

node *nodeList = (node *)0;

int getval(char *name)
{
	node *ptr;

	for(ptr = nodeList;ptr != (node *)0; ptr = ptr->nextNode)
 	{
 		if(!strcmp(ptr->name,name))
 		{
 			return ptr->val;
 		}
 	}

 	return -1;
}

node *getNode(char *name)
 {
 	node *ptr;
 	for(ptr = nodeList;ptr != (node *)0; ptr = ptr->nextNode)
 	{
 		if(!strcmp(ptr->name,name))
 		{
 			return ptr;
 		}
 	}

 	return (node *)0;
 }

int getType(char *name)
 {
 	node *ptr;
 	for(ptr = nodeList;ptr != (node *)0; ptr = ptr->nextNode)
 	{
 		if(!strcmp(ptr->name,name))
 		{
 			return ptr->type;
 		}
 	}
 }

int isExist(char *name, int level)
 {
 	node *ptr;
 	for(ptr = nodeList;ptr != (node *)0; ptr = ptr->nextNode)
 	{
 		if(!strcmp(ptr->name,name) && ptr->level >= level)
 		{
 			return 1;
 		}
 	}
 	return 0;
 }

void insert(char *name,int type, int line, int val, int level)
 {
 	node *ptr = nodeList;

 	printf("here");

 	ptr = getNode(name);

 	if(ptr == (node *)0)
 	{
 		ptr = (node *)malloc(sizeof(node));
 		strcpy(ptr->name,name);
 		ptr->cnt = 0;
 		ptr->type = type;
 		ptr->line[(ptr->cnt)++] = line;
 		ptr->val = val;
 		ptr->level = level;
 	}
 	else
 	{
 		ptr->line[(ptr->cnt)++] = line;
 	}
 	ptr->nextNode = nodeList;
 	nodeList = ptr;
 }

 void sym_dump()
 {
 	node *ptr = nodeList;
 	int cnt;
 	printf("\n");
 	printf("Name\t\tType\t\tisfunc\t\tval\t\tlevel\t\tline\n");
 	for(;ptr!=(node *)0;ptr=ptr->nextNode){
 		printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t",ptr->name,ptr->type,ptr->isfunc,ptr->val,ptr->level);
 		for(cnt=0;cnt<ptr->cnt;cnt++)
 			printf("%d ",ptr->line[cnt]);
 		printf("\n");
 	}
 }