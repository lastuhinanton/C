#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNTS 21

int main(void)
{
    srand(time(NULL));

    int i;
    char array[COUNTS] = {'\0'};
    
    for (i = 0; i < COUNTS - 1; i++)
    {
       array[i] = rand() % 25 + 97;
    }

    printf("%s\n", array);

     
    return 0;
}

