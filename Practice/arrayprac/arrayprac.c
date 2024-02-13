#include <stdio.h>

int main()
{
    int numbs[4], i;

    for (i = 0; i < 4; i++)
    {
        scanf("%d", &numbs[i]);
    }

    printf("\n");

    for (i = 0; i < 4; i++)
    {
        printf("%d ", numbs[i]);
    }

    return 0;
}