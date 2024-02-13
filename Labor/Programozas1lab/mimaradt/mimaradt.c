#include <stdio.h>

int main()
{
    double num, sum = 0.0;
    char rem;

    while (scanf("%lf", &num) == 1)
    {
        sum = sum + num;
    }

    printf("%.3f\n", sum);

    while (scanf("%c", &rem) == 1)
    {
        printf("%c", rem);
    }
    
    return 0;
}
