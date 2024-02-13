#include <stdio.h>
#include <float.h>
#include <math.h>

int main(void)
{

    double num, sqrt;
    int i = 0;

    scanf("%lf %lf", &num, &sqrt);

    do
    {
        printf("%d %.16E\n", i, sqrt);

        sqrt = sqrt / 2 + num / (2 * sqrt);

        i++;
    } while (fabs(sqrt * sqrt - num) / num >= 10 * DBL_EPSILON);

    printf("%d %.16E\n", i, sqrt);

    sqrt = sqrt / 2 + num / (2 * sqrt);

    i++;

    return 0;
}