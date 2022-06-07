#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i = 123;
    char c[50] = {"123"};
    //sprintf(c, "%d", i);
    //itoa(i, c, 10);                                 // itoa() and is not ANSI C standard and don't work with gcc on Linux

    for (int j = 0; j < 50; j++)                    // You can create a itoa() function by your own
    {                                               // The alternative is sprintf() that has 3 arguments (array, string, value);
        printf("%c|", c[j]);                        // atoi() works fine
    }
    
    printf("\n");

    int t = atoi(c);
    printf("%d\n", t);

    float f = atof(c);
    printf("%f\n", f);
    
    char symbol = 100;
    printf("%c\n", symbol);

    return 0;
}

