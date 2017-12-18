/*
 
 Course      :   COEN 11 (Advanced C Programming)
 Project     :   #4
 Filename    :   project4.c
 Date        :   10/09/17
 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// struct nested in a union
union Status
{
    char schoolname[20];
    float salary;
    int retirementyear;
};


// union containing the three possible options
typedef struct Person
{
    char name[20];
    int age;
    union Status status;
}Person;


// protos
int addPerson(char name[], int age, union Status status);
int deletePerson(char name[]);
int listPeople();


// globals
Person people[10]; //array of structs nested in a union
int count=0;


int main()
{
    int x;
    while (1)
    {
        printf("Enter 1 to add a person\nEnter 2 to remove a person\nEnter 3 for the list of people\nEnter 4 to quit\n");
        scanf("%d",&x);
        
        switch(x)
        {
                char name[20];
                int age;
                union Status status;
                
            case 1:
                printf("Enter a name: ");
                scanf("%s", name);
                printf("\nEnter an age: ");
                scanf("%d", &age);
                
                if(age<=21)
                {
                    printf("\nWhat is the name of your school: ");
                    scanf("%s", status.schoolname);
                }
                else if(age>21 && age<65)
                {
                    printf("\nWhat is your salary per month?: ");
                    scanf("%f", &status.salary);
                }
                else
                {
                    printf("\nWhat year did you retire?: ");
                    scanf("%d", &status.retirementyear);
                }
                
                if(addPerson(name,age,status)==-1)
                {
                    printf("\nYour name was not added due to the amount of people in our system already");
                }
                break;
                
            case 2:
                printf("\nWhat name would you like to remove: ");
                scanf("%s", name);
                
                if(deletePerson(name) == -1)
                {
                    printf("\nThe person you are trying to remove does not exist");
                }
                break;
                
            case 3:
                listPeople();
                break;
                
            case 4:
                exit(0);
                break;
                
            default:
                continue;
        }
    }
}


int addPerson(char name[], int age, union Status status)
{
    Person newPerson;
    strcpy(newPerson.name,name);
    age = newPerson.age;
    
    // grouping logic
    if(age <= 21)
    {
        strcpy(newPerson.status.schoolname, status.schoolname);
    }
    else if(age > 21 && age < 65)
    {
        newPerson.status.salary = status.salary;
    }
    else if(age >= 65)
    {
        newPerson.status.retirementyear = status.retirementyear;
    }
    
    if(count == 10)
    {
        return -1;
    }
    newPerson = people[count++];
    return 0;
}


int deletePerson(char name[])
{
    int i;
    for(i=0; i<count; i++)
    {
        if(strcmp(name, people[i].name) == 0)
        {
            people[i]=people[--count];
            return 0;
        }
    }
    return -1;
}


int listPeople()
{
    int i;
    for(i = 0; i < count; i++)
    {
        printf("\nName: %s", people[i].name);
        printf("\nAge: %d", people[i].age);
        
        if(people[i].age <= 21)
        {
            printf("\nSchool: %s\n", people[i].status.schoolname);
        }
        if(people[i].age > 21 && people[i].age < 65)
        {
            printf("\nSalary: %.2f\n", people[i].status.salary);
        }
        else if(people[i].age >= 65)
        {
            printf("\nRetirement year: %d\n", people[i].status.retirementyear);
        }
    }
    return 0;
}
