/*

Course      :   COEN 11 (Advanced C Programming)
Project     :   #2
Filename    :   project2.c
Date        :   09/24/17

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// protos
int addtable(void);
int removetable(void);
int list(void);

// globals
int count = 0;
char waitlist[10][11];
int party[10];


int main()
{
    int i;
    int option;
    
    for(i=0; i<10; i++)
        waitlist[i][0] = '\0';
    
    system("clear");
    while(1)
    {
        printf("\n Enter 1 to reserve a table. \n Enter 2 to remove a table. \n Enter 3 to list all of the tables. \n Enter 4 to quit. \n");
        
        scanf("%d", &option);
        
        switch(option)
        {
            case 1:
                if(addtable() != 0)
                    continue;
                break;
                
            case 2:
                removetable();
                break;
                
            case 3:
                list();
                break;
                
            case 4:
                return 0;
                
            default:
                printf("Enter a number between one AND four");
        }
    }
}


int addtable()
{
    int i, tablesize, available;
    char name[10];
    
    printf("\n What is your name?: \n");
    scanf("%s", name);
    
    for(i=0; i<count; i++)
    {
        if(strcmp(name, waitlist[i]) == 0) // read the documentation on this function
        {
            printf("Sorry, that name is already taken! \n");
            return 1;
        }
    }
    
    printf("\n What is your party size? \n");
    scanf("%d", &tablesize);
    
    party[count]=tablesize;
    
    strcpy(waitlist[count], name);
    
    count++;
    
    if(count == 10)
        available == 0;
    
    if(available == 1)
        printf("\n Sorry, all of the tables are taken. \n");
    
    return 0;
}


int removetable()
{
    int i, j, size, didcancel=0;
    
    printf("\n What was the size of your table? \n");
    scanf("%d", &size);
    
    for(i=0; i<count; i++)
    {
        if(size>=party[i])
        {
            for(j=0; j<9; j++)
            {
                party[j]=party[j+1]; // someone cancels so open up another party
                strcpy(waitlist[j], waitlist[j+1]);
            }
            count--;
            didcancel=1;
            printf("\n Deletion of the reservation was successful! \n");
            return 0;
        }
    }
    if(didcancel=0)
        printf("\n Deletion of the reservation NOT successful! \n");
    return 0;
}


int list()
{
    int i;
    for(i=0; i<count; i++)
    {
        printf("Name: %s, Party Size: %d \n", waitlist[i], party[i]);
    }
    return 0;
}

