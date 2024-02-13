#include <stdio.h>

int main()
{
    int a, b, c, i = 0;

    scanf("%d %d", &a, &b);

    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;

    }
    
    printf("%d", a);

    return 0;
}
