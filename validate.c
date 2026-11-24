#include "inv_s.h"

int validate(char *filename)
{
    int len=strlen(filename);

    if(filename[len-1]!='t' || filename[len-2]!='x' || filename[len-3]!='t' || filename[len-4]!='.')
    {
        printf("Error:%s has a invlaid file extension.\n",filename);
        return FAILURE;
    }
    

    FILE *fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf(" %s doesn't exist.\n",filename);
        return FAILURE;
    }

    if(fgetc(fp)==EOF)
    {
        printf("Error:%s File is empty.\n",filename);
        return FAILURE;
    }
    fclose(fp);
    return SUCCESS;
}


