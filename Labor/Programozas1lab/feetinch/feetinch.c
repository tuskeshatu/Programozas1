#include <stdio.h>

typedef struct imperial
{
    int foot, inch;
} imperial;

double imperial_to_metric(struct imperial imperial)
{
    return ((double)imperial.inch / 12 + imperial.foot) * 0.3048;
}

struct imperial plus(struct imperial imp1, struct imperial imp2)
{
    struct imperial impsum;

    impsum.foot = impsum.inch = 0;

    if (imp1.inch + imp2.inch >= 12)
    {
        impsum.foot++;   
    }

    impsum.foot += imp1.foot + imp2.foot;

    impsum.inch = (imp1.inch + imp2.inch) % 12;

    return impsum;
    
}

int main(void)
{
    imperial curimp;

    while (scanf("%d %d", &curimp.foot, &curimp.inch) == 2)
    {
        printf("%.4f ", imperial_to_metric(curimp));
    }
    
    return 0;
}