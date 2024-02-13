#include <stdio.h>

int main()
{
    int ai, i = 0;

    scanf("%d", &ai);

    while (ai != 1)
    {

        if (ai % 2 == 0)
        {
            ai = ai / 2;
        }
        else
        {
            ai = 3 * ai + 1;
        }
        
        i++;
    }

    printf("%d", i);

    return 0;
}
