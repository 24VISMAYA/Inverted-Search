#ifndef inv_s
#define inv_s

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS 0
#define FAILURE 1

typedef struct node
{
    char *data;
	struct node *link;
}Slist;

typedef struct sub
{
    char filename[27];
    int word_count;
    struct sub *link;
}sub_node;

typedef struct main
{
    char word[27];
    int filecount;
    sub_node *sublink;
    struct main *link;
}main_node;



int validate(char *filename);
int insert_at_last(Slist **head,char *filename);
void print_list(Slist *head);
int create_ds(main_node **arr,Slist **head);
int create_main_n(main_node **arr,char *word,char *filename);
int create_sub_n(sub_node **sublink,char *filename);
void display(main_node **arr);
int search(main_node **arr,char *word);
int save(main_node **arr,char *file);
int update_ds(main_node **arr,Slist **head,char *file);
void delete_file_node(Slist **head, char *fname);

#endif