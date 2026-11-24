#include "inv_s.h"
int insert_at_last(Slist **head, char *filename)
{
    
    Slist *newnode=malloc(sizeof(Slist));
    if(newnode==NULL)
	{
	    printf("Memory allocation failed.\n");
	    return 1;
	}
	newnode->data=filename;
	newnode->link=NULL;
	
	if(*head==NULL)
	{
	    *head=newnode;
	    return SUCCESS;
	}
	Slist *temp=*head;
    Slist *prev=NULL;
	while(temp!=NULL)
	{
        if(strcmp(filename,temp->data)==0)
        {
            printf("Warning: %s is a duplicate file.\n",filename);
             free(newnode);
             return FAILURE;
        }
        prev=temp;
	    temp=temp->link;   
	}
	prev->link=newnode;
	return SUCCESS;
}

void print_list(Slist *head)
{
    
	if (head == NULL)
	{
		printf("List is empty\n");
	}
    Slist *temp=head;
	    while (temp!=NULL)		
	    {
            printf("head -> ");
		    printf("%s -> ", temp -> data);
		    temp = temp -> link;
	    }

	    printf("NULL\n");
    
}


int create_main_n(main_node **arr,char *word,char *filename)
{
    main_node *mnode = malloc(sizeof(main_node));
    if(mnode==NULL)return FAILURE;
    strcpy(mnode->word,word);
    mnode->filecount=1;
    mnode->link=NULL;
    create_sub_n(&(mnode->sublink),filename);
    *arr=mnode;
    return SUCCESS;
}

int create_sub_n(sub_node **sublink,char *filename)
{
    sub_node *snode=malloc(sizeof(sub_node));
    if(snode==NULL)return FAILURE;
    strcpy(snode->filename,filename);
    snode->word_count=1;
    snode->link=NULL;
    *sublink=snode;
    return SUCCESS;
}

void delete_file_node(Slist **head, char *fname)
{
    Slist *temp = *head;
    Slist *prev = NULL;

    while (temp != NULL)
    {
        if (strcmp(temp->data, fname) == 0)
        {
            if (prev == NULL)
                *head = temp->link;  
            else
                prev->link = temp->link;

            free(temp);
            return;
        }
        prev = temp;
        temp = temp->link;
    }
}