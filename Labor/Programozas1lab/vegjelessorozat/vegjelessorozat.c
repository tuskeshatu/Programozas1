#include <stdio.h>

int main()
{
    int num, sum = 0, i = 0;

    while (1)
    {
        scanf("%d", &num);

        if (num == 0)
            break;
        
        sum = sum + num;

        i++;
    }

    printf("%.2f", (double)sum/i);
    

    return 0;
}
