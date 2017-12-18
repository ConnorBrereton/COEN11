/*
 
 Course      :   COEN 11 (Advanced C Programming)
 Project     :   #8
 Filename    :   project8.c
 Date        :   11/05/17
 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// node setup
typedef struct node
{
    char name[20];
    int size;
    struct node *next;
}node;

node* head[4]={NULL,NULL,NULL,NULL};
node* tail[4]={NULL,NULL,NULL,NULL};


// protos
void add_party(int, char name[], int size);
void delete_party(char name[], int size);
void list_parties();
void change_partysize();

void write_to_file(char *filename);
void read_to_list(char *filename);

void wipe_nodes();

void write_to_bin(char *filename);
void bin_to_list(char *filename);


// node data -> .txt file
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
            fprintf(fp, "Error");
        
        while(p != NULL)
        {
            fprintf(fp, "%s\t\t %d\n", p->name, p->size);
            p = p -> next;
        }
    }
    fclose(fp);
    return;
}


// .txt file -> node
void read_to_list(char *filename)
{
    int mined_partysize;
    char mined_partyname[20];
    
    FILE *fp;
    fp = fopen(filename, "r");
    
    if (fp == NULL)
    {
        printf("Empty file!\n");
        return;
    }
    
    // get past the header template
    fseek(fp, 51, SEEK_SET);
    
    while(fscanf(fp, "%s%d", mined_partyname, &mined_partysize) == 2)
    {
        if(mined_partysize == 0)
            printf("\nThat is not a valid command. Party not added!\n");
        
        if(mined_partysize >= 1 && mined_partysize <= 2)
            add_party(0, mined_partyname, mined_partysize);
        
        else if(mined_partysize >= 3 && mined_partysize <= 4)
            add_party(1, mined_partyname, mined_partysize);
        
        else if(mined_partysize >= 5 && mined_partysize <= 6)
            add_party(2, mined_partyname, mined_partysize);
        
        else if(mined_partysize >= 7)
            add_party(3, mined_partyname, mined_partysize);
    }
    fclose(fp);
    return;
}


// node data -> .bin file
void write_to_bin(char *filename)
{
    int i = 0;
    node *p=NULL;
    
    FILE *fp;
    fp = fopen(filename, "wb");
    
    if(fp == NULL)
    {
        printf("Empty file!\n");
        return;
    }
    
    for(i=0; i<4; i++)
    {
        p=head[i];
        
        if(p == NULL)
        {
            printf("Error\n");
        }
        
        while(p != NULL)
        {
            fwrite(p, sizeof(node), 1, fp);
            p = p -> next;
        }
    }
    fclose(fp);
    return;
}


// wipe all data in nodes
void wipe_nodes()
{
    int i;
    node *p=NULL;
    
    for(i=4; i>0; i--)
    {
        p=head[i];
        
        if(p == NULL)
        {
            printf("Nodes are clear!\n");
        }
        
        while(p != NULL)
        {
            delete_party(p->name, p->size); // cant call name and size
            p = p -> next;
        }
    }
}


// .bin file -> node
void bin_to_list(char *filename)
{
    int ret;
    node temp;
    
    FILE *fp;
    fp = fopen(filename, "rb");
    
    if (fp == NULL)
    {
        printf("Null file!\n");
        return;
    }
    
    while((ret = fread(&temp, sizeof(node), 1, fp) > 0))
    {
        if(temp.size == 0)
            printf("\nThat is not a valid command. Party not added!\n");
        
        if(temp.size >= 1 && temp.size <= 2)
            add_party(0, temp.name, temp.size);
        
        else if(temp.size >= 3 && temp.size <= 4)
            add_party(1, temp.name, temp.size);
        
        else if(temp.size >= 5 && temp.size <= 6)
            add_party(2, temp.name, temp.size);
        
        else if(temp.size >= 7)
            add_party(3, temp.name, temp.size);
    }
    fclose(fp);
    return;
}


// recursive reverse
void reverse_nodes(int i, node *p, node *q)
{
    if(p == NULL)
    {
        printf("Error, no nodes!\n");
        return;
    }
    
    
    if(p->next == NULL)
    {
        printf("LOL, only one node! Can't reverse!\n");
        head[i] = p;
    }
    
    else
    {
        reverse_nodes(i, p->next, p);
    }
    
    p->next = q;
    return;
}


int main(int argc, char *argv[])
{
    int x, i;
    read_to_list(argv[1]);
    bin_to_list(argv[2]);
    while (1)
    {
        fflush(stdin);
        printf("\n\nEnter 1 to add a party\nEnter 2 to remove a party\nEnter 3 for the list of the party\nEnter 4 to change party size.\nEnter 5 to quit (write to .txt file).\nEnter 6 to read from bin file.\nEnter 7 to reverse the list.\n\n");
        
        scanf("%d",&x);
        
        int size;
        char name[20];
        
        switch(x)
        {
                
            case 1:
                printf("\nParty Name: ");
                scanf("%s", name);
                printf("\nParty Size: ");
                scanf("%d", &size);
                
                if(size == 0)
                    printf("\nThat is not a valid command. Party not added!\n");
                
                if(size >= 1 && size <= 2)
                    add_party(0, name, size);
                
                else if(size >= 3 && size <= 4)
                    add_party(1, name, size);
                
                else if(size >= 5 && size <= 6)
                    add_party(2, name, size);
                
                else if(size >= 7)
                    add_party(3, name, size);
                
                break;
                
            case 2:
                printf("\nSize of party to delete: ");
                scanf("%i", &size);
                
                delete_party(NULL, size);
                break;
                
            case 3:
                list_parties();
                break;
                
            case 4:
                change_partysize(name, size);
                break;
                
            case 5:
                write_to_file(argv[1]);
                write_to_bin(argv[2]);
                
                exit(0);
                break;
                
            case 6:
                wipe_nodes();
                bin_to_list(argv[2]);
                break;
                
            case 7:
                for(i=0; i<4; i++)
                {
                    reverse_nodes(i, head[i], NULL);
                }
                break;
                
            default:
                continue;
        }
    }
}


void add_party(int h, char *name, int size)
{
    int number;
    int i=0;
    int breaker = 0;
    
    node *p;
    node *new_item;
    
    new_item = (node *)malloc(sizeof(node));
    
    strcpy(new_item->name,name);
    new_item->size = size;
    
    // Case: empty list
    if(head[h] == NULL && tail[h] == NULL)
    {
        head[h] = new_item;
        tail[h] = head[h];
        new_item->next = NULL;
        return;
    }
    
    for(i=0; i<4; i++)
    {
        p = head[i];
        while(p != NULL)
        {
            if(strcmp(p->name,name) == 0)
            {
                printf("\nSorry, that name is already taken\n");
                free(new_item);
                return;
            }
            p = p->next;
        }
    }
    tail[h]->next = new_item;
    new_item->next = NULL;
    tail[h] = new_item;
}


void delete_party(char *name, int size)
{
    int i=0;
    int breaker = 0;
    node *p;
    node *previous;
    
    
    if(name != NULL)
    {
        for(i=0; i<4; i++)
        {
            p = previous = head[i];
            
            while(p != NULL)
            {
                int c = strcmp(p->name,name);
                if(c==0)
                {
                    
                    breaker = 1;
                    break;
                }
                else
                {
                    previous = p;
                    p = p -> next;
                }
            }
            if(breaker == 1)
                break;
            
        }
    }
    else
    {
        int group = -1;
        
        if(size == 1 || size == 2)
            group = 0;
        
        if(size == 3 || size == 4)
            group = 1;
        
        if(size == 5 || size == 6)
            group = 2;
        
        if(size >= 7)
            group = 3;
        
        for(i = group; i > -1; i--)
        {
            p = head[i];
            previous = head[i];
            
            while(p != NULL)
            {
                if(p->size <= size)
                {
                    breaker = 1;
                    break;
                }
                
                else
                {
                    previous = p;
                    p = p-> next;
                }
            }
            if(breaker)
                break;
        }
    }
    
    // Case: null pointer
    if(p == NULL)
    {
        printf("\nNothing was found!");
        return;
    }
    printf("\n %s is being removed here!", p->name);
    
    // Case: empty list
    if(head[i] == tail[i] && head[i] == NULL)
    {
        printf("\nList is empty!\n");
        return;
    }
    
    // Case: one element
    else if(p == tail[i] && p == head[i])
    {
        head[i] = NULL;
        tail[i] = NULL;
        free(p);
    }
    
    // Case: delete head
    else if(p == head[i])
    {
        head[i] = head[i] -> next;
        free(p);
    }
    
    // Case: delete tail
    else if(p == tail[i])
    {
        tail[i] = previous;
        tail[i] -> next = NULL;
        free(p);
        free(p);
    }
    
    // Case: delete middle
    else
    {
        previous -> next = p -> next;
        free(p);
    }
    
}


void list_parties()
{
    int i = 0;
    node *p=head;
    
    for(i=0; i<4; i++)
    {
        printf("-----\ngroup %d\n",i);
        
        p=head[i];
        
        while(p != NULL)
        {
            printf("\n%s, %d\n", p->name, p->size);
            p=p->next;
        }
    }
}


int find_group(int size)
{
    if(size == 1 || size == 2)
        return 0;
    
    else if(size == 3 || size == 4)
        return 1;
    
    else if(size == 5 || size == 6)
        return 2;
    
    else if(size >= 7)
        return 3;
    
    else
        return -1;
}


void change_partysize()
{
    int i, size;
    int group = 0;
    int old_group = -1;
    int holder = -1;
    int new_group = find_group(&size);
    
    char *name[20];
    
    node* p;
    
    printf("\nWhat name is your party under?\n");
    scanf("%s", name);
    
    printf("\nWhat would you like to change the size to?\n");
    scanf("%d", &size);
    
    for(i=0; i<4; i++)
    {
        p = head[i];
        while(p != NULL)
        {
            if(strcmp(p->name,name) == 0)
            {
                holder = p->size;
                break;
            }
            p = p->next;
        }
        if(holder != -1)
            break;
    }
    if(holder == -1)
    {
        printf("\nCant find name");
        return;
    }
    else
        old_group = find_group(holder);
    
    if(holder == size)
        return;
    
    else if(old_group == new_group)
    {
        p->size = size;
        return;
    }
    else
    {
        delete_party(name,NULL);
        add_party(new_group, name, size);
    }
}
