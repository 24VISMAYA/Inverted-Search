#include "inv_s.h"

int main(int argc,char *argv[])
{
    if(argc==1)
    printf("Error.No input file provided.\n");

    Slist *head=NULL;
    for(int i=1;i<argc;i++)
    {
        if(validate(argv[i])==SUCCESS)
        {
            insert_at_last(&head,argv[i]);
        }
    }

    print_list(head);
    main_node *arr[27]={NULL};
    int option,create_flag=0,update_flag=0;
    printf("Select to search :\n1.Create database.\n2.Display database.\n3.Search database.\n4.Update database.\n5.Save database.\n6.Exit.\nEnter your choice : ");

    while (1)
	{
		scanf("%d", &option);	
		switch (option)
        {
            case 1:
            {
                if(create_flag==0)
                {
                    if(create_ds(arr,&head)==SUCCESS)
                    {
                        printf("Database created successfully.\n");
                        create_flag=1;
                    }
                    else
                    {
                        printf("Database failed to create.\n");
                    }
                }
                else
                {
                    printf("Error:Database already created.\n");
                }
                break;  
            }
            case 2:
            {
                display(arr);
                break;
            }
            case 3:
            {
                char word[50];
                printf("Enter the word to search: \n");
                scanf("%s",word);
                if(search(arr,word)==FAILURE)
                printf("The word not found.\n");
                break;
            }
            case 4:
            {
                if(create_flag==1)
                {
                    printf("Error:Database already created.Cannot update now.\n");
                }
                else if (update_flag==1)
                {
                    printf("Error:Database already updates.Cannot update twice.\n");
                }
                else
                {
                    char backup_file[50];
                    printf("Enter the backup filename: \n");
                    scanf("%s",backup_file);
                    if(update_ds(arr,&head,backup_file)==SUCCESS)
                    {
                        printf("Database updated successfully.\n");
                        update_flag=1;
                    }
                    else
                    {
                        printf("Database failed to update successfully.\n");
                    }
                }

                break;
            }
            case 5:
            {
                char file[30];
                printf("Enter the filename: ");
                scanf("%s",file);
                int len=strlen(file);
                if(len<5 || file[len-1]!='t' || file[len-2]!='x' || file[len-3]!='t' || file[len-4]!='.')
                {    
                    printf("Error: %s-->Invalid file format\n",file);
                    break;
                }
                if(save(arr,file)==SUCCESS)
                    printf("Database saved successfully.\n");
                else
                    printf("Failed to save database.\n");
                break;
            }
            case 6:
            {
                printf("Exiting...\n");
                
                return 0;
            }
        }
    }
    
}    


