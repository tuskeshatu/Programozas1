#include <stdio.h>

int main()
{

    int num = 0, prevnum = 0, i = 0;

    if (scanf("%d", &num) != 1)
        return 0;

    prevnum = num;

    if (scanf("%d", &num) == 1)
    {
        if (num > prevnum)
        {
            while (num > prevnum)
            {
                printf("%d ", prevnum);

                prevnum = num;

                scanf("%d", &num);
            }
        }

        else if (num < prevnum)
        {
            while (num < prevnum)
            {
                printf("%d ", prevnum);

                prevnum = num;

                scanf("%d", &num);
            }
        }
    }

    printf("%d", prevnum);

    return 0;
}
