#include <stdio.h>

int main ()
{
    int numbs[10], i;

    for (i = 0; i < 10; i++)
    {
        scanf("%d", &numbs[i]);
    }

    printf("\n\n");

    for (i = 9; i >= 0; i--)
    {
        printf("%d ", numbs[i]);
    }
    
    
    return 0;
}