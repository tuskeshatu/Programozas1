#include <stdio.h>

int main(void)
{
    double num, prevdist, dist = 1;

    scanf("%lf", &num);

    if (num == 0.00)
    {
        return 0;
    }
    

    dist = prevdist = num;

    do
    {
        /* printf("\n%5E", dist); */

        prevdist = dist;

        dist = dist / 2;

    } while (num + dist > num);

    printf("%.5E", (num + prevdist) - num);

    return 0;
}
