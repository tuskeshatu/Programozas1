// eletem elso nagyobb lelekzetvetelu projektje
// editors note: ez mar egy fokkal jobb kivettem a hatvanyozast, a z.h. keresest meg a math.h dolgokat kulon fuggvenybe
//  ------------------------------------------------------------------
//                  K O V A C S         L E V E N T E

#include <stdio.h>

// hatvanyozas
long double hatvany(long double a, long double n)
{
    long double ret = 1;
    int i = 1;
    printf("\nakkor hatvanyozzunk!");

    while (i <= n)
    {
        ret = ret * a;
        i++;
    }

    return ret;
}

// z.h. kereses
long double zerushely(long double a, int num, int denom)
{
    long double left, right = a, mid, eps1 = 1e-8, middenom, anum;
    int i = 1;

    printf("\n\n-------------------------------------------------------------------------------------------\nzerushely kereses leventetol szeretettel");

    if (a < 0)
    {
        printf("\na fuggveny: -(x^%d)", denom);
        if (denom > num)
        {
            left = -hatvany(1 / a, denom);
            anum = hatvany(a, num);
            printf("+(%Lf^%d)\n", a, num);
        }
        else
        {
            left = -hatvany(a, num);
            anum = left;
            printf("-(%Lf^%d)\n", a, num);
        }
        right = 0;
    }
    else
    {
        printf("\na fuggveny: x^%d", denom);
        if (denom > num)
        {
            right = hatvany(1 / a, denom);
            anum = hatvany(a, num);
            printf("-(%Lf^-%d)\n", a, num);
        }
        else
        {
            right = hatvany(a, num);
            anum = right;
            printf("+(%Lf^%d)\n", a, num);
        }
        left = 0;
    }

    while (right - left > eps1)
    {

        long double mid = (left + right) / 2;

        middenom = mid;
        if (a < 0)
        {
            middenom = -hatvany(mid, denom);
        }
        else
        {
            middenom = hatvany(mid, denom);
        }

        if (middenom - anum > 0)
            right = mid;
        else
            left = mid;

        printf("\nz.h.: %Lf\nleft: %Lf\nright: %Lf\n", (right + left) / 2, left, right);
    }

    return (right + left) / 2;
}

// floor
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
int kerek(long double a)
{
    int whole;
    long double frac;

    if (a < 0)
    {
        whole = lekerek(a) + 1;

        frac = a - whole;

        if (frac <= -0.5)
        {
            return whole - 1;
        }
        else
        {
            return whole;
        }
    }
    else
    {
        whole = lekerek(a);

        frac = a - whole;

        if (frac < 0.5)
        {
            return whole;
        }
        else
        {
            return whole + 1;
        }
    }
}

// abszolutertek
long double absz(long double a)
{
    if (a < 0)
    {
        return -a;
    }

    return a;
}

void tort(long double rational)
{
    printf("\n\n-------------------------------------------------------------------------------------------\ntortatiro leventetol szeretettel\n");

    long double eps = 1e-4, frac, near;
    int num, denom, whole, i = 1;

    whole = lekerek(rational);
    frac = rational - whole;
    near = kerek(frac);

    num = denom = 1;

    while (absz((long double)num / denom - frac) > eps)
    {

        near = kerek(frac * i);
        num = near;
        denom = i;
        i++;

        printf("%d/%d,\n%Lf\n", num, denom, (long double)num / denom);
    }

    num = num + denom * whole;

    printf("a  =  %Lf,\n\ntort:  %d/%d  =  %Lf\n\n", rational, num, denom, (long double)num / denom);
}

int main()
{

    // valtozok: a: alap n: kitevo nv: negativ kitevu eseten n reciproka i: whilehoz res: eredmeny
    long double a, n, nv, res = 1;
    int whole;

    printf("\n\n-------------------------------------------------------------------------------------------\nhatvanyozas leventetol szeretettel\n");

    printf("\nalap a: ");
    scanf("%Lf", &a);

    printf("\nkitevo n: ");
    scanf("%Lf", &n);

    whole = n;

    // ha negativ a kitevo, akkor abszolut ertek
    if (n < 0)
    {
        nv = -n;
    }
    else
    {
        nv = n;
    }

    // actual hatvanyozas

    // tortkitevo check
    if (whole - nv != 0)
    {

        // num/denom atiras
        int num, denom;
        tort(nv);

        // z.h. keresovel fgv alakitassal gyok kereses

        res = zerushely(a, num, denom);
    }

    else
    {

        // normal hatvanyozas

        res = hatvany(a, nv);
    }

    // ha negativ a kitevo, akkor az abszolut erteku kitevoju hatvany reciproka [a^(-n) = 1/(a^n)]
    if (n < 0)
    {
        res = 1 / res;
    }

    printf("\n\n%Lf a %Lf. hatvanyon: %Lf", a, n, res);

    return 0;
}