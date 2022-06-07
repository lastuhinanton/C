#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define width 65
#define height 25

typedef struct {
    int x, y;
    int w;
} TRacket;

char arr[height][width + 1];
TRacket racket;

void initRacket()
{
    racket.w = 7;
    racket.x = (width - racket.w) / 2;
    racket.y = height - 2;
}

void PutRacket()
{
   for (int i = racket.x; i < racket.x + racket.w; i++)
   {
       arr[racket.y][i] = '@';
   }
}

void init()
{
    for (int i = 0; i < width; i++)
    {
        arr[0][i] = '#';
    }
    arr[0][width] = '\0';

    arr[1][0] = '#';
    for (int i = 1; i < width - 1; i++)
    {
        arr[1][i] = ' ';
    }
    arr[1][width - 1] = '#';
    arr[1][width] = '\0';

    for (int i = 2; i < height - 1; i++)
    {
        strncpy(arr[i], arr[1], width + 1);
    }

    strncpy(arr[height - 1], arr[0], width + 1);
}

void show()
{
    for (int i = 0; i < height; i++)
    {
        printf("%s", arr[i]);
        printf("\n");
    }
}

int main(void)
{
    initRacket();
    
    init();    

    PutRacket();

    show();

    return 0;
}















































































