#include <stdio.h>

int perfect(int num)
{
    int curdiv, sumdiv = 0;

    for (curdiv = 1; curdiv < num; curdiv++)
    {
        if (num % curdiv == 0)
        {
            sumdiv += curdiv;
        }
    }

    if (sumdiv == num)
    {
        return 1;
    }

    return 0;
    
}

int main(void)
{
    int in = 6;
    int out = perfect(in);
    printf("%d\n", out);
    return 0;
}