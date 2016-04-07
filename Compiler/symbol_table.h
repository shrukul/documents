#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ast.h"

struct symbol {
	const char *name;
	int type;
	struct symbol *next;
	} *head = NULL;
	
void add_symbol(int type_specifier, const char* identifier)
{
	if(head == NULL)
	{
		head = (struct symbol*) malloc(sizeof(struct symbol));
		head->type = type_specifier;
		head->name = identifier;
		//printf("Symbol Added\n");
		return;
		}
	struct symbol *temp = (struct symbol *) malloc(sizeof(struct symbol));
	temp->name = identifier;
	temp->type = type_specifier;
	struct symbol *p = head;
	while(p->next != NULL)
	p = p->next;
	p->next = temp;
	//printf("Success!");
}
	
int lookup(const char* identifier)
{
	if(head == NULL)
	return 0;
	
	struct symbol * temp = head;
	while(temp != NULL)
	{
		if(!strcmp(identifier,"a"))
		return 1;
		temp = temp->next;
	}
	return 0;
}
