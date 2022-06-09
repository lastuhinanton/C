// gcc game.c -w -lSDL2 // FOR RUNING WITH LIBRARIES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>


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

void moveRacket(int x)
{
    racket.x = x;
    if (racket.x < 1)
    {
        racket.x = 1;
    }
    
    if (racket.x + racket.w >= width)
    {
        racket.x = width - 1 - racket.w;
    }
}

void setcur(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}


// #define CMIN 1

// #define CTIME 1

int khbit(void)
{
    int cnt = 0;
    int error;
    static struct termios Otty, Ntty;

    tcgetattr(0, &Otty);
    Ntty = Otty;

    Ntty.c_iflag = 0;                       /* input mode */
    Ntty.c_oflag = 0;                       /* output mode */
    Ntty.c_lflag &= ~ICANON;                /* raw mode */
    Ntty.c_cc[VMIN] = 1;                 /* minumum chars to wait for CMIN */
    Ntty.c_cc[VTIME] = 1;               /* minimum wait time CTIME */

    if (0 == (error = tcsetattr(0, TCSANOW, &Ntty)))
    {
        struct timeval tv;
        error += ioctl(0, FIONREAD, &cnt);
        error += tcsetattr(0, TCSANOW, &Otty);
        tv.tv_sec = 0;
        tv.tv_usec = 1;                   /* insert a minimal delay */
        select(1, NULL, NULL, NULL, &tv);
    }

    return (error == 0 ? cnt : -1);
}

int getch(void)
{
    char ch;
    int error;
    static struct termios Otty, Ntty;

    fflush(stdout);
    tcgetattr(0, &Otty);
    Ntty = Otty;

    Ntty.c_iflag = 0;                   /* input mode           */
    Ntty.c_oflag = 0;                   /* output mode          */
    Ntty.c_lflag &= ~ICANON;            /* line settings        */

#if 1
    /* disable echoing the char as it is typed */
    Ntty.c_lflag &= ~ECHO;               /* disable echo         */
#else
    /* enable echoing the char as it is typed */
    Ntty.c_lflag |= ECHO;               /* enable echo           */
#endif


    Ntty.c_cc[VMIN] = CMIN;             /* minimum chars to wait for */
    Ntty.c_cc[VTIME] = CTIME;           /* minimum wait time */

#if 0
/*
 * use this to flush the input buffer before blocking for new input
 */
#define FLAG TCSAFLUSH
#else
/*
 * use this to return a char from the current input buffer, or block if
 * no input is waiting.
 */
#define FLAG TCSANOW
    
#endif
    
    if (0 == (error = tcsetattr(0, FLAG, &Ntty)))
    {
        error = read(0, &ch, 1);        /* get char from stdin */
        error += tcsetattr(0, FLAG, &Otty);
    }

    return (error == 1 ? (int) ch: -1 );
}


int main(void)
{
    int ch, cnt;
    static struct termios Otty, Ntty;

    tcgetattr(0, &Otty);
    Ntty = Otty;
    Ntty.c_lflag &= ~ECHO;

    fflush(stdout);

    // while (1)
    // {
      //   if (1 <= (cnt = khbit()))
        // {
          //   printf("I work\n");
            // break;
        // }
        // printf("I'm working\n");

    // }



    //struct termios term;

    //tcgetattr(STDIN_FILENO, &term);
    //term.c_lflag &= ~(ICANON | ECHO);
    //tcsetattr(STDIN_FILENO, 0, &term);

    initRacket();

    int test = 0;


    bool gameIsRunning = true;
    while (gameIsRunning)
    { 

        init();    
        PutRacket();
        show();


        if (1 <= (cnt = khbit())) { moveRacket(racket.x - 1); }

        if (1 <= (cnt = khbit())) { moveRacket(racket.x + 1); }

        fflush(stdout);

        test++;
        printf("I'm working -- %d -- %d\n", test, cnt = khbit());
        cnt = 0;

        setcur(0, 0);
    }
    
    system("reset");

    return 0;
}















































































