/*
 
 Course      :   COEN 11 (Advanced C Programming)
 Project     :   #5
 Filename    :   project5.c
 Date        :   10/17/17
 
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define S 10

// protos
void delete(int size);
void list(void);
void insert(char *name, int size);


// node setup
typedef struct Node
{
    char name[S];
    int size;
    struct Node *next;
}node;


// head & tail setup
node *head=NULL, *tail=NULL;


int main()
{
    int x,i, size;
    char name[S];
    
    head = NULL;
    tail = NULL;
    
    while (1)
    {
        char name[SIZE];
        int size;
        
        fflush(stdin);
        
        printf("\nPress 1 to reserve a table.\nPress 2 to cancel.\nPress 3 to list.\nPress 4 to exit \n");
        scanf("%d", &x);
        
        switch(x)
        {
            case 1:
                printf("Enter a name: ");
                scanf("%s", name);
                
                printf("Enter size: ");
                scanf("%d", &size);
                
                insert(name,size);
                break;

            case 2:
                printf("Enter a size: ");
                scanf("%d", &size);
                
                delete(size);
                break;
                
            case 3:
                list();
                break;
                
            case 4:
                exit(0);
                break;
                
            default:
                continue;
        }
    }
}


void insert(char *name, int size)
{
    node *newentry,*p=head;
    
    // allocates the memory
    if ((newentry = (node*)malloc (sizeof (node))) == (node*)NULL)
    {
        printf("\nMemory allocated\n");
        return;
    }
    
    // LL Case: no nodes
    if(head==NULL)
    {
        head=newentry;
        tail=newentry;
        
        strcpy(newentry->name, name);
        newentry->size=size;
        
        return;
    }
    
    // search for duplicates
    while(p!=NULL)
    {
        if(strcmp(p->name,name) == 0)
        {
            printf("\nThis name already exists\n");
            free(newentry);
            return;
        }
        p=p->next;
    }
    
    strcpy(newentry->name, name);
    newentry->size=size;
    tail->next=newentry;
    newentry->next=NULL;
    tail=newentry;
}


void list()
{
    node *p=head;
    while(p!=NULL)
    {
        printf("%s, %d\n", p->name, p->size);
        p=p->next;
    }
}


void delete(int size)
{
    node *p=head;
    
    // Case: empty list
    if(p==NULL)
        return;
    
    // Case: one node, just delete right away
    if(head==tail)
    {
        if(head->size<=size)
        {
            head=NULL;
            tail=NULL;
            free(p);
        }
        return;
    }
    
    // Case: more than one node, control memory leak
    while(p->next->next != NULL)
    {
        if(p->next->size<=size)
        {
            p->next = p->next->next;
            return;
        }
    }
    
    // Case: new size > old size, set new head and delete old node
    if(p->size<=size)
    {
        head=p->next;
        free(p);
        return;
    }
    // Case: old size > new size, set new head and delete
    if(p->next->size<=size)
    {
        node *q=p->next;
        p->next=NULL;
        free(q);
        tail=p;
    }
}
