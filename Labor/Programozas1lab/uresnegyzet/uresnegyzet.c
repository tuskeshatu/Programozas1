#include <stdio.h>

int main()
{
    int i, j, col = 1, sidelen;

    scanf("%d", &sidelen);

    for (i = 0; i <= sidelen*sidelen; i++)
    {
        if (i == 0)
        {
            for (j = 0; j < sidelen; j++)
            {
                printf("x");
            }

            printf("\n");

            i = i + sidelen;
        }
        else if (i > sidelen*(sidelen-1))
        {
            for (j = 0; j < sidelen; j++)
            {
                printf("x");
            }

            printf("\n");

            i = i + sidelen;
        }
        
        else if (col == 1)
        {
            printf("x");
            col++;
        }
        else if (col == sidelen)
        {
            printf("x\n");
            col = 1;
        }
        
        else
        {
            printf(".");
            col++;
        }
        
    }

    return 0;
}
