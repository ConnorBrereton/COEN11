/*
 
 Course      :   COEN 11 (Advanced C Programming)
 Project     :   #3
 Filename    :   project3.c
 Date        :   10/03/17
 
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// protos
int gettable(void);
int cancel(void);
int list(void);


// struct setup
typedef struct party
{
    char name[10];
    int partysize;
}party;


// globals
party waitlist[10];
int count=0;


int main()
{
    int x, i;
    
    system("clear");
    while(1)
    {
        printf("\nPress 1 to reserve a table.\nPress 2 to cancel your appointment.\nPress 3 to list appointments.\nPress 4 to exit.\n");
        scanf("%d", &x); // this is the UI
        
        switch(x) // input controller
        {
            case 1:
                if(gettable()!=0)
                    continue;
                break;
                
            case 2:
                cancel();
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


int gettable()
{
    int i,tblsize,available;
    char name[10];
    
    party *p = waitlist;
    
    printf("Enter Your Name: ");
    scanf("%s", &name);
    
    if(count == 10)
    {
        printf("\n Sorry, the restaurant is full right now\n");
        return 1;
    }
    
    for(i=0; i<count; i++; p++)
    {
        if(strcmp(name,p->name) == 0)
        {
            printf("This name already is taken...Try again with another name");
            return 1;
        }
    }
    p = waitlist;
    p += count;
    
    printf("\nHow many people are in your party?: ");
    scanf("%d", &tblsize);
    
    // update the data
    p->partysize=tblsize;
    strcpy(p->name,name);
    
    count++;
    return 0;
}


int cancel()
{
    int i,size,j;
    
    printf("What is the size of the table?: ");
    scanf("%d", &size);
    
    party *p = waitlist;
    
    for(i=0; i<count; i++)
    {
        if(size>= p->partysize)
        {
            for(j=i; j<count-1; j++; p++)
            {
                p->partysize=(p+1)->partysize; // add another spot to the array
                strcpy(p->name,(p+1)->name); // adds another spot and points it back
            }
            count--;
            printf("Your cancelation was successful");
            return 0;
        }
    }
    return 0;
}


int list()
{
    int i;
    
    party *p = waitlist;
    
    for(i=0; i<count; i++; p++)
    {
        printf("%s: %d\n", p->name, p->partysize);
    }
    return 0;
}
