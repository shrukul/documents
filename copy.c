#include<stdio.h>
#include<stdlib.h>

struct node
{
	enum {black, red} colour;
	int info;
	struct node *lchild;
	struct node *rchild;
	struct node *parent;    
};

int find(int item, struct node **loc);
void insert(int);
void insert_balance(struct node *nptr);
void del(int);
void del_balance(struct node *ptr);
void rotate_left(struct node *ptr);
void rotate_right(struct node *ptr);
struct node *succ(struct node *ptr);
void inorder(struct node *ptr);
void display(struct node *ptr, int level);
struct node *root;
struct node *sentinel; // for parent of root node and NULL nodes

int main()
{
	int choice, num;
	sentinel = (struct node *)malloc(sizeof(struct node));
	sentinel->info = -1;
	sentinel->colour = black;
	root = sentinel;
	
	while(1)
	{
		printf("\nChoose from the following:\n\n ");
		printf("1. Insert\n");
		printf("2. Delete\n");
		printf("3. Inorder Traversal\n");
		printf("4. Dsiplay\n");
		printf("5. Quit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
				printf("Enter the number to be inserted: ");
				scanf("%d", &num);
				insert(num);
				break;
			case 2:
				printf("Enter the number to be deleted: ");
				scanf("%d", &num);
				del(num);
				break;
			case 3:
				inorder(root);
				break;
			case 4:
				display(root, 1);
				break;
			case 5:
				return 0;
			default:
				printf("Please enter a correct choice\n");
		}
	}
}

int find(int item, struct node **loc)
{
	struct node *ptr;
	if(root == sentinel)
	{
		*loc = sentinel;
		return 0;
	}
	if(item == root->info)
	{
		*loc = root;
		return 1;
	}
	
	if(item < root->info)
		ptr = root->lchild;
	else
		ptr = root->rchild;
	
	while(ptr!=sentinel)
	{
		if(item == ptr->info)
		{
			*loc = ptr;
			return 1;
		}
		if(item < ptr->info)
			ptr = ptr->lchild;
		else
			ptr = ptr->rchild;
	}
	
	*loc = sentinel;
	return 0;
}

void insert(int ikey)
{
	struct node *temp, *ptr, *par;
	par = sentinel;
	ptr = root;
	while(ptr != sentinel)
	{
		par = ptr;
		if(ikey < ptr->info)
			ptr = ptr->lchild;
		else if(ikey > ptr->info)
			ptr = ptr->rchild;
		else
		{
			printf("Duplicate\n");
			return;
		}
	}
		
	temp = (struct node *)malloc(sizeof(struct node));
	temp->info = ikey;
	temp->lchild = sentinel;
	temp->rchild = sentinel;
	temp->colour = red;
	temp->parent = par;
	
	
	if(par == sentinel)
		root = temp;
	else if(temp->info < par->info)
		par->lchild = temp;
	else
		par->rchild = temp;
		
	insert_balance(temp);
}

void insert_balance(struct node *nptr)
{
	struct node *uncle, *par, *grand_par;
	while(nptr->parent->colour == red)
	{
		par = nptr->parent;
		grand_par = par->parent;
		
		if(par == grand_par->lchild)
		{
			uncle = grand_par->rchild;
			
			if(uncle->colour == red)
			{
				par->colour = black;
				uncle->colour = black;
				grand_par->colour = red;
				nptr = grand_par;
			}
			
			else
			{
				if(nptr == par->rchild)
				{
					rotate_left(par);
					nptr = par;
					par = nptr->parent;
				}
				
				par->colour = black;
				grand_par->colour = red;
				rotate_right(grand_par);
			}
		}
		
		else
		{
			if(par == grand_par->rchild)
			{
				uncle = grand_par->lchild;
				
				if(uncle->colour == red)
				{
					par->colour = black;
					uncle->colour = black;
					grand_par->colour = red;
					nptr = grand_par;
				}
				
				else
				{
					if(nptr == par->lchild)
					{
						rotate_right(par);
						nptr = par;
						par = nptr->parent;
					}
					
					par->colour = black;
					grand_par->colour = red;
					rotate_left(grand_par);
				}
			}
		}
	}
	root->colour = black;
}

void del(int item)
{
	struct node *child, *ptr, *successor;
	if(!find(item, &ptr))
	{
		printf("Item not present \n");
		return;
	}
	
	if(ptr->lchild != sentinel || ptr->rchild != sentinel)
	{
		successor = succ(ptr);
		ptr->info = successor->info;
		ptr = successor;
	}
	
	if(ptr->lchild != sentinel)
		child = ptr->lchild;
	else
		child = ptr->rchild;
	
	child->parent = ptr->parent;
	
	if(ptr->parent == sentinel)
		root = child;
	else if(ptr == ptr->parent->lchild)
		ptr->parent->lchild = child;
	else
		ptr->parent->rchild = child;
		
	if(child == root)
		child->colour = black;
	else if(ptr->colour == black)
	{
		if(child != sentinel)
			child->colour = black;
		else
			del_balance(child);
	}
}

void del_balance(struct node *nptr)
{
	struct node *sib;
	while(nptr != root)
	{
		if(nptr == nptr->parent->lchild)
		{
			sib = nptr->parent->rchild;
			if(sib->colour == red)
			{
				sib->colour = black;
				nptr->parent->colour = red;
				rotate_left(nptr->parent);
				sib = nptr->parent->rchild;
			}
			
			if(sib->lchild->colour == black && sib->rchild->colour == black)
			{
				sib->colour = red;
				if(nptr->parent->colour == red)
				{
					nptr->parent->colour = black;
					return;
				}
				
				else
					nptr = nptr->parent;
			}
			
			else
			{
				if(sib->rchild->colour == black)
                {
                    sib->lchild->colour = black;
                    sib->colour = red;
                    rotate_right(sib);
                    sib = nptr->parent->rchild;
                }
                
                sib->colour = nptr->parent->colour;
                nptr->parent->colour = black;
                sib->rchild->colour = black;
                rotate_left(nptr->parent);
                return;
			}
		}

        else
        {
            sib=nptr->parent->lchild;

            if(sib->colour == red)
            {
                sib->colour = black;
                nptr->parent->colour = red;
                rotate_right(nptr->parent);
                sib = nptr->parent->lchild;
            }

            if(sib->rchild->colour == black && sib->lchild->colour == black)
            {
                sib->colour = red;
    
                if(nptr->parent->colour == red)
                {
                    nptr->parent->colour = black;
                    return;
                }

                else
                    nptr = nptr->parent;
            }

            else
            {
                if(sib->lchild->colour == black)
                {
                    sib->rchild->colour = black;
                    sib->colour = red;
                    rotate_left(sib);
                    display(root,1);
                    sib = nptr->parent->lchild;
                }
            
                sib->colour = nptr->parent->colour;
                nptr->parent->colour = black;
                sib->lchild->colour = black;
                rotate_right(nptr->parent);
                return;
            }
        }
	}
}

void rotate_left(struct node *pptr)
{
    struct node *aptr;
    
    aptr = pptr->rchild;
    pptr->rchild = aptr->lchild;
    
    if(aptr->lchild != sentinel)
        aptr->lchild->parent = pptr;

    aptr->parent = pptr->parent;

    if(pptr->parent == sentinel)
        root = aptr;
    else if(pptr == pptr->parent->lchild)
        pptr->parent->lchild = aptr;
    else
        pptr->parent->rchild = aptr;
    
    aptr->lchild = pptr;
    pptr->parent = aptr;
}

void rotate_right(struct node *pptr)
{
    struct node *aptr;
    
    aptr = pptr->lchild;
    pptr->lchild = aptr->rchild;
    
    if(aptr->rchild != sentinel)
        aptr->rchild->parent = pptr;

    aptr->parent = pptr->parent;

    if(pptr->parent == sentinel)
        root = aptr;
    else if(pptr == pptr->parent->rchild)
        pptr->parent->rchild = aptr;
    else
        pptr->parent->lchild = aptr;
    
    aptr->rchild = pptr;
    pptr->parent = aptr;
}

struct node *succ(struct node *loc)
{
    struct node *ptr = loc->rchild;

    while(ptr->lchild != sentinel)
    {
        ptr = ptr->lchild;
    }
    
    return ptr;
}

void inorder(struct node *ptr)
{
    if(ptr != sentinel)
    {
        inorder(ptr->lchild);
        printf("%d ",ptr->info);
        inorder(ptr->rchild);
    }
}

void display(struct node *ptr, int level)
{
    int i;

    if(ptr != sentinel)
    {
        display(ptr->rchild,level+1);
        printf("\n");

        for(i=0; i<level; i++)
            printf(" ");
        
        printf("%d",ptr->info);

        if(ptr->colour == red)
            printf("^");
        else
            printf("*");

        display(ptr->lchild,level+1);
    }
}
