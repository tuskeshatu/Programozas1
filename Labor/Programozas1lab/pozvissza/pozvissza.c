#include <stdio.h>

int main()
{
    int num[100], i;

    for (i = 0; i < 100; i++)
    {
        num[i] = -1;
    }
    
    i = 0;

    while (1)
    {
        scanf("%d", &num[i]);

        if (num[i] == 0)
            break;
        
        i++;
    }
    
    for (i = 99; i >= 0; i--)
    {
        if (num[i] > 0)
        {
            printf("%d ", num [i]);
        }
        
    }
    

    return 0;
}
