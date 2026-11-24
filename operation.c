#include "inv_s.h"

int create_ds(main_node **arr,Slist **head)
{
    Slist *temp=*head;
    char word[50];
    int index;
    while(temp!=NULL)
    {
        FILE *fp =fopen(temp->data,"r");
        while(fscanf(fp,"%s",word)!=EOF)
        {
            if(word[0]>='a' && word[0]<='z')
                index=word[0]-'a';
            else if(word[0]>='A' && word[0]<='Z')    
                index=word[0]-'A';
            else
                index=26;    
            
            if(arr[index]==NULL)
            {
                if(create_main_n(&arr[index],word,temp->data)==FAILURE)
                {
                    fclose(fp);
                    return FAILURE;
                }
            }
            else
            {
                main_node *m_curr=arr[index];
                main_node *m_prev=NULL;

                while(m_curr!=NULL && strcmp(m_curr->word,word)!=0)
                {
                    m_prev=m_curr;
                    m_curr=m_curr->link;
                }

                if(m_curr==NULL)
                {
                   if( create_main_n(&(m_prev->link),word,temp->data)==FAILURE)
                   {
                    fclose(fp);
                    return FAILURE;
                   }
                }
                else
                {
                    sub_node *s_curr=m_curr->sublink;
                    sub_node *s_prev=NULL;
                    while(s_curr!=NULL && strcmp(s_curr->filename,temp->data)!=0)
                    {
                        s_prev=s_curr;
                        s_curr=s_curr->link;
                    }
                    if(s_curr!=NULL)
                    {
                        s_curr->word_count++;
                    }
                    else
                    {
                        if(create_sub_n(&(s_prev->link),temp->data)==FAILURE)
                        {
                            fclose(fp);
                            return FAILURE ;
                        }
                        m_curr->filecount++;
                    }
                }
            } 
        }
        fclose(fp);
        temp=temp->link;
    }
    return SUCCESS;
}

void display(main_node **arr)
{
    printf("[Index]   [Word]        [FileCount]   [FileName]   [WordCount]\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < 27; i++)
    {
        if (arr[i] != NULL)
        {
            main_node *m_temp = arr[i];
            while (m_temp != NULL)
            {
                printf("[%2d]      %-13s %-13d ", i, m_temp->word, m_temp->filecount);
                sub_node *s_temp = m_temp->sublink;
                while (s_temp != NULL)
                {
                    printf("%-12s %d   ", s_temp->filename, s_temp->word_count);
                    s_temp = s_temp->link;
                }
                printf("\n");
                m_temp = m_temp->link;
            }
        }
    }
}


int search(main_node **arr,char *word)
{
    int index;
    if(word[0]>='a' && word[0]<='z')
    index=word[0]-'a';
    else if(word[0]>='A' && word[0]<='Z')
    index=word[0]-'A';
    else 
    index=26;
    
    if(arr[index]==NULL)
        return FAILURE;
    
    main_node *m_temp=arr[index];
    while(m_temp!=NULL)
    {
        if(strcmp(m_temp->word,word)==0)
        {
            printf("Word %s is present in %d files\n",m_temp->word,m_temp->filecount);
            sub_node *s_temp=m_temp->sublink;
            while(s_temp!=NULL)
            {
                printf("In %s => %d times\n",s_temp->filename,s_temp->word_count);
                s_temp=s_temp->link;
            }
            return SUCCESS;
        }
        else
        m_temp=m_temp->link;
    }  
    if(m_temp==NULL)
        return FAILURE;
    else
        return SUCCESS;
}


int save(main_node **arr,char *file)
{
    FILE *fp=fopen(file,"w");
    if(fp==NULL)return FAILURE;
    for (int i = 0; i < 27; i++)
    {
        if (arr[i] != NULL)
        {
            main_node *m_temp = arr[i];
            while (m_temp != NULL)
            {
                fprintf(fp,"#%d;%s;%d;",i,m_temp->word,m_temp->filecount);
                sub_node *s_temp = m_temp->sublink;
                while (s_temp != NULL)
                {
                    fprintf(fp,"%s;%d;", s_temp->filename, s_temp->word_count);
                    s_temp = s_temp->link;
                }
                fprintf(fp,"#\n");
                m_temp = m_temp->link;
            }
        }
    }
    fclose(fp);
    return SUCCESS;
}


int update_ds(main_node **arr,Slist **head,char *file)
{
    if(validate(file)==FAILURE)return FAILURE;

    FILE *fp=fopen(file,"r");
    char first=fgetc(fp);
    fseek(fp,-2,SEEK_END);
    char last=fgetc(fp);
    
    if(first!='#' || last!='#')
    {
        printf("Error: %s is not a valid backup file(missing '#'mark).\n",file);
        fclose(fp);
        return FAILURE;
    }
    rewind(fp);
    int index,file_c,word_c;
    char word[50],fname[50];
    while(fscanf(fp,"#%d;%[^;];%d;",&index,word,&file_c)!=EOF)
    {
        main_node *m_new=malloc(sizeof(main_node));
        strcpy(m_new->word,word);
        m_new->filecount=file_c;
        m_new->sublink=NULL;
        m_new->link=NULL;

        if(arr[index]==NULL)
            arr[index]=m_new;
        else
        {
            main_node *temp=arr[index];
            while(temp->link!=NULL)
                temp=temp->link;
            temp->link=m_new;    
        }    
        
        sub_node *s_temp=NULL;

        for(int i=0;i<file_c;i++)
        {
            fscanf(fp,"%[^;];%d;",fname,&word_c);

            delete_file_node(head,fname);
            sub_node *s_new=malloc(sizeof(sub_node));
            strcpy(s_new->filename,fname);
            s_new->word_count=word_c;
            s_new->link=NULL;
            if(m_new->sublink==NULL)
            {
                m_new->sublink=s_new;
                s_temp=s_new;
            }
            else
            {
                s_temp->link=s_new;
                s_temp=s_temp->link;
            }
        }
        fscanf(fp,"#\n");
    }
return SUCCESS;
}