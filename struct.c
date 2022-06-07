#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct decor {
    int length, width, hight;
    char name[51];
} s_decor;


int main(void)
{
    scanf("%d %d %d ", &s_decor.length, &s_decor.width, &s_decor.hight);

    fgets(s_decor.name, 51, stdin);
    s_decor.name[strlen(s_decor.name) - 1] = '\0';

    printf("%d %d %d %s\n", s_decor.length, s_decor.width, s_decor.hight, s_decor.name);
    
    return 0;
}
 
