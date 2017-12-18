#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define S 100 //macro for the buffer size

int main(int argc, char *argv[])
{
    
    int ret;
    int x;
    int i;
    
    char read_buffer[S];
    char write_buffer[S];
    char key = atoi(argv[1]);
    
    
    if (argc!=4)
    {
        printf("Enter the folling 3 things: level of encryption (0-255), binary file to encrypt, name of file to save encrypted data to \n");
        return 0;
    }
    
    FILE *fp_read=fopen(argv[2], "rb"), *fp_write=fopen(argv[3], "wb");
    
    if(fp_read==NULL || fp_read==NULL)
    {
        printf("Error with one or more files. \n");
        return 0;
    }
    
    while (1)
    {
        printf("\nEnter 1 to ENCRYPT/DECRYPT\nEnter 2 to QUIT\n");
        scanf("%d", &x);
        
        switch(x)
        {
            case 1:
                while((ret=fread(read_buffer, sizeof(char), 100, fp_read)) > 0)
                {
                    for(i=0; i<ret; i++)
                        write_buffer[i] = read_buffer[i]^key;
                    fwrite(write_buffer, sizeof(char), ret, fp_write);
                }
                fclose(fp_read);
                fclose(fp_write);
                break;
                
            case 2:
                printf("Quitting\n");
                return 0;
                
            default:
                printf("This is not an option");
                return 0;
        }
    }
}
