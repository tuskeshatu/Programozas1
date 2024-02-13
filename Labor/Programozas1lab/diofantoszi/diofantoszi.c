#include <stdio.h>

int main()
{
    int a, b, c, x, y;
    double ydoub;

    scanf("%d %d %d", &a, &b, &c);

    for (x = 1; x < c-y; x++)
    {
        y = (c-a*x)/b;
        ydoub = (c-a*x)/b;

        if (y <= 0)
        {
            break;
        }
        

        if (ydoub == y)
        {
            if (a*x+b*y == c)
            {
                printf("%d %d\n", x, y);
            }
            
        }
        
    }
    
    return 0;
}
