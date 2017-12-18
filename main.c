// main.c
// Created by Connor Brereton on 11/12/2017


//declare and init global variables
#include "list.h"
#include "files.h"

node* head[4]={NULL,NULL,NULL,NULL};
node* tail[4]={NULL,NULL,NULL,NULL};

//thread variable
pthread_mutex_t save_lock;

//
// main function
//

//
// autosave with thread function
//

void *autosave(char *filename)
{
    while(1)
    {
	pthread_mutex_lock(&save_lock);
        write_to_file(filename);
        pthread_mutex_unlock(&save_lock);
        sleep(5);
    }
}

int main(int argc, char *argv[])
{
    int x, i;
    read_to_list(argv[1]);
    bin_to_list(argv[2]);
    
    pthread_t saver;
    pthread_create(&saver, NULL, autosave, argv[3]);
    
    while (1)
    {
        fflush(stdin);
        printf("\n\nEnter 1 to add a party\nEnter 2 to remove a party\nEnter 3 for the list of the party\nEnter 4 to change party size.\nEnter 5 to quit (write to .txt file).\nEnter 6 to read from bin file.\nEnter 7 to reverse the list.\n\n");
        
        scanf("%d",&x);
        char name[20];
        int size;
        pthread_mutex_lock(&save_lock);
        switch(x)
        {
                
            case 1:
                printf("\nParty Name: ");
                scanf("%s", name);
                printf("\nParty Size: ");
                scanf("%d", &size);
                if(size == 0)
                {
                    printf("\nThat is not a valid command. Party not added!\n");
                }
                if(size >= 1 && size <= 2)
                {
                    add_party(0, name, size);
                }
                else if(size >= 3 && size <= 4)
                {
                    add_party(1, name, size);
                }
                else if(size >= 5 && size <= 6)
                {
                    add_party(2, name, size);
                }
                else if(size >= 7)
                {
                    add_party(3, name, size);
                }
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
		pthread_cancel(saver);
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
        pthread_mutex_unlock(&save_lock);
    }
}

