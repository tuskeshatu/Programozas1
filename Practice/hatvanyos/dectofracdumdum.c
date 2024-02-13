#include <stdio.h>
#include <math.h>

//tizedestorteket szamlalo/nevezo alakba kozelitessel
int main()
{
    double n, eps = 1e-8, frac, num , denom, near;
    int whole, j = 1;

    scanf("%lf", &n);

    whole = floor(n);
    frac = n-whole;
    near = round(frac);
    

    printf("whole: %d, frac: %lf\n", whole, frac);

    num = denom = 1;

    while(fabs(num/denom-frac)>eps)
    {

        near = round(frac*j);
        num = near;
        denom = j;
        j++;

        printf("%lf/%lf,\n%lf\n", num, denom, num/denom);

    }

    num = num + denom*whole;
printf("\n-------------------------------------------------------------------------------------------\n\na  =  %lf,\n\ntort:  %lf/%lf  =  %lf", n, num, denom, num/denom)
    ;

    return 0;
}
