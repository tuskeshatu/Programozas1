#include <stdio.h>

int ipow(int base, int exp)
{
    int pow = 1;

    for (int i = 0; i < exp; i++)
    {
        pow *= base;
    }
    
    return pow;
}

int main(void)
{
    int in = 3;
    int out = ipow(3, 2);
    printf("%d\n", out);
    return 0;
}