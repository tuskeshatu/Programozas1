#include <stdio.h>

int lekerek(long double a)
{
    if (a < 0)
    {
        return (int)a - 1;
    }
    else
    {
        return (int)a;
    }
}
// round
int main()
{
    int whole;
    long double frac, a;

    scanf("%Lf", &a);

        if (a < 0)
    {
        whole = lekerek(a) + 1;

        printf("%d\n", whole);

        frac = a - whole;

        if (frac <= -0.5)
        {
            printf("%d", whole - 1);
        }
        else
        {
            printf("%d", whole);
        }
    }
    else
    {
        whole = lekerek(a);

        frac = a - whole;

        if (frac < 0.5)
        {
            printf("%d", whole);
        }
        else
        {
            printf("%d", whole + 1);
        }
    }
}