#include <stdio.h>

int main()
{

    int num, minpoz, maxneg, intpozcheck, intnegcheck;

    intpozcheck = intnegcheck = 0;

    while (scanf("%d", &num) == 1)
    {
        if (num < 0)
        {
            intnegcheck++;

            if (intnegcheck == 1)
                maxneg = num;

            if (num > maxneg)
                maxneg = num;
        }

        if (num > 0)
        {
            intpozcheck++;

            if (intpozcheck == 1)
                minpoz = num;

            if (num < minpoz)
                minpoz = num;
        }

        
    }

    if (intnegcheck > 0)
        printf("%d ", maxneg);
    else
        printf("--- ");

    if (intpozcheck > 0)
        printf("%d", minpoz);
    else
        printf("---");

    return 0;
}
