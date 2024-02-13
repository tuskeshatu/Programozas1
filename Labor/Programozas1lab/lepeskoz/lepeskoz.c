#include <stdio.h>

int main()
{
    
    int min, ret, max, step = 1;

    scanf("%d %d", &min, &max);

    ret = min;

    while (ret <= max)
    {
        printf("%d ", ret);

        ret = ret + step;

        step++;
    }
    

    return 0;
}
