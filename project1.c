/*
 
 Course      :   COEN 11 (Advanced C Programming)
 Project     :   #1
 Filename    :   project1.c
 Date        :   09/19/17
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// proto
int division(int, int);


int main()
{
    int divisor, quotient, x, score;
    score = 0;
    srand((int) time (NULL));
    
    for (x=0; x<10; x++)
    {
        
        divisor = rand() % 12 + 1;
        quotient = rand() % 13;
        int answer = division(quotient, divisor);
        score += answer;
    }
    
    printf("\n You scored %d out of 10 \n\n", score);
    return 0;
}


int division(int quotient, int divisor)
{
    int input = 0;
    int dividend;
    
    dividend = divisor * quotient;
    
    printf("The dividend is: %d \n", dividend);
    printf("The divisor is: %d \n", divisor);
    printf("Enter the quotient: ");
    
    scanf("%d", &input);
    
    if (input == quotient)
    {
        printf("\nYou got the answer right! \n\n");
        return 1;
    }
    
    else
    {
        printf("\nYou got the answer wrong! \n\n");
        return 0;
    }
}
