#include <stdio.h>

int pyramid(int count)
{
    int sqrsum = 0;

    for (int i = 0; i <= count; i++)
    {
        sqrsum += i * i;
    }
    
    return sqrsum;
}


int main(void)
{
    int in = 3;
    int out = pyramid(in);
    printf("%d\n", out);
    return 0;
}