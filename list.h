//
// Created by Connor Brereton on 11/13/2017
//


// header file for the list functions

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct node
{
    char name[20];
    int size;
    struct node *next;
}node;

void add_party(int, char name[], int size);
void delete_party(char name[], int size);
void list_parties();
void change_partysize();
void wipe_nodes();

extern node* head[4];
extern node* tail[4];
