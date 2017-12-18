// files.c
// Created by Connor Brereton on 11/12/2017


//
// write (TEXT)
//


//include the header files
#include "list.h"
#include "files.h"

void write_to_file(char *filename)
{
    FILE *fp;
    
    fp = fopen(filename, "w");
    
    if(fp == NULL)
    {
        printf("Empty file!\n");
        return;
    }
    
    int i = 0;
    node *p=NULL;
    
    fprintf(fp, "Name\t\tGroup Size\n----------------------------------\n");
    
    for(i=0; i<4; i++)
    {
        p=head[i];
        if(p == NULL)
            return;
        
        while(p != NULL)
        {
            fprintf(fp, "%s\t\t %d\n", p->name, p->size);
            p = p -> next;
        }
    }
    fclose(fp);
    return;
}


//
// read (TEXT)
//


void read_to_list(char *filename)
{
    FILE *fp;
    
    int mined_partysize;
    char mined_partyname[20];
    
    fp = fopen(filename, "r");
    
    if (fp == NULL)
    {
        printf("Empty file!\n");
        return;
    }
    
    fseek(fp, 51, SEEK_SET);
    while(fscanf(fp, "%s%d", mined_partyname, &mined_partysize) == 2)
    {
        if(mined_partysize == 0)
        {
            printf("\nThat is not a valid command. Party not added!\n");
        }
        if(mined_partysize >= 1 && mined_partysize <= 2)
        {
            add_party(0, mined_partyname, mined_partysize);
        }
        else if(mined_partysize >= 3 && mined_partysize <= 4)
        {
            add_party(1, mined_partyname, mined_partysize);
        }
        else if(mined_partysize >= 5 && mined_partysize <= 6)
        {
            add_party(2, mined_partyname, mined_partysize);
        }
        else if(mined_partysize >= 7)
        {
            add_party(3, mined_partyname, mined_partysize);
        }
    }
    fclose(fp);
    return;
}


//
// write (BINARY)
//


void write_to_bin(char *filename)
{
    FILE *fp;
    
    fp = fopen(filename, "wb");
    
    if(fp == NULL)
    {
        printf("Empty file!\n");
    }
    
    int i = 0;
    node *p=NULL;
    
    for(i=0; i<4; i++)
    {
        p=head[i];
        if(p == NULL)
            return;

        while(p != NULL)
        {
            fwrite(p, sizeof(node), 1, fp);
            p = p -> next;
        }
    }
    fclose(fp);
    return;
}


//
// read (BINARY)
//


void bin_to_list(char *filename)
{
    FILE *fp;
    int ret;
    
    fp = fopen(filename, "rb");
    
    if (fp == NULL)
    {
        printf("Null file!\n");
        return;
    }
    
    node temp;
    
    while((ret = fread(&temp, sizeof(node), 1, fp) > 0))
    {
        if(temp.size == 0)
        {
            printf("\nThat is not a valid command. Party not added!\n");
        }
        if(temp.size >= 1 && temp.size <= 2)
        {
            add_party(0, temp.name, temp.size);
        }
        else if(temp.size >= 3 && temp.size <= 4)
        {
            add_party(1, temp.name, temp.size);
        }
        else if(temp.size >= 5 && temp.size <= 6)
        {
            add_party(2, temp.name, temp.size);
        }
        else if(temp.size >= 7)
        {
            add_party(3, temp.name, temp.size);
        }
    }
    fclose(fp);
    return;
}
