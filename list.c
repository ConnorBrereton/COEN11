// list.c
// Created by Connor Brereton on 11/12/2017


//
// wipe all nodes before reading binary file
//


//include the header file
#include "files.h"
#include "list.h"

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


//
// reverse the nodes
//


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


//
//add function
//


void add_party(int h, char *name, int size)
{
    //declare file pointer
    FILE *fp;
    
    //to be used by fscanf
    int number;
    
    //create a new node
    int i=0;
    int breaker = 0;
    node *p;
    node *new_item;
    
    new_item = (node *)malloc(sizeof(node)); // allocate memory the size of the struct
    
    strcpy(new_item->name,name);
    new_item->size = size;
    
    if(head[h] == NULL && tail[h] == NULL) // if an empty list, create a head and tail
    {
        head[h] = new_item;
        tail[h] = head[h];
        new_item->next = NULL;
        return;
    }
    
    //traversal
    for(i=0; i<4; i++)
    {
        p = head[i];
        while(p != NULL)
        {
            //check that no repeating names. delete nodes that do have repeating names
            if(strcmp(p->name,name) == 0)
            {
                printf("\nSorry, that name is already taken\n"); //TODO: use a flag to get rid of start msg
                free(new_item);
                return;
            }
            p = p->next; //go to the next node in the list
        }
    }
    tail[h]->next = new_item;
    new_item->next = NULL;
    tail[h] = new_item;
    
    
}


//
//delete function
//


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
            p = previous = head[i]; //make sure previous trails behind head
            while(p != NULL)
            {
                int c = strcmp(p->name,name);
                if(c==0){
                    
                    breaker = 1;
                    break;
                }
                else
                {
                    previous = p;
                    p = p -> next;
                }
            }
            if(breaker==1)
                break;
            
        }
    }
    else
    {
        int group = -1;
        
        if(size == 1 || size == 2)
        {
            group = 0;
        }
        if(size == 3 || size == 4)
        {
            group = 1;
        }
        if(size == 5 || size == 6)
        {
            group = 2;
        }
        if(size >= 7)
        {
            group = 3;
        }
        
        for(i = group; i > -1; i--)
        {
            p = head[i]; //removed the node*
            previous = head[i]; //removed the node*
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
    
    if(p == NULL)
    {
        printf("\nNothing was found!");
        return;
    }
    printf("\n %s is being removed here!", p->name);
    
    
    if(head[i] == tail[i] && head[i] == NULL) // case 1, empty list
    {
        printf("\nList is empty!\n");
        return;
    }
    else if(p == tail[i] && p == head[i]) // case 2, one element
    {
        head[i] = NULL;
        tail[i] = NULL;
        free(p);
    }
    else if(p == head[i]) // case 3, delete from the head
    {
        head[i] = head[i] -> next;
        free(p);
    }
    else if(p == tail[i]) // case 4, delete from tail
    {
        tail[i] = previous;
        tail[i] -> next = NULL;
        free(p);
        free(p);
    }
    else // case 5, delete from middle
    {
        previous -> next = p -> next;
        free(p);
    }
    
}


//
// list function
//


void list_parties(void)
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
    {
        return 0;
    }
    else if(size == 3 || size == 4)
    {
        return 1;
    }
    else if(size == 5 || size == 6)
    {
        return 2;
    }
    else if(size >= 7)
    {
        return 3;
    }
    else
        return -1;
}


//
// change function
//


void change_partysize()
{
    char *name[20];
    int size;
    int group = 0;
    printf("\nWhat name is your party under?\n");
    scanf("%s", name);
    
    printf("\nWhat would you like to change the size to?\n");
    scanf("%d", &size);
    
    int new_group = find_group(&size);
    
    node* p;
    int old_group = -1;
    int holder = -1;
    int i;
    for(i=0; i<4; i++)
    {
        p = head[i];
        while(p != NULL)
        {
            //check that no repeating names. delete nodes that do have repeating names
            if(strcmp(p->name,name) == 0)
            {
                holder = p->size;
                break;
            }
            p = p->next; //go to the next node in the list
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
    {
        old_group = find_group(holder);
    }
    
    if(holder == size)
    {
        return;
    }
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
