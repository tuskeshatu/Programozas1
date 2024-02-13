#include <stdio.h>

int gcd(long long unsigned num1, long long unsigned num2)
{
    long long unsigned temp;

    while (num2 != 0)
    {
        temp = num1 % num2;
        num1 = num2;
        num2 = temp;

        if (num2 == 1)
            return 1;
        
    }

    return num1;
}


int main(void)
{
    int binom1, binom2;
    long long unsigned num[40], denom[40], res = 1;

    scanf("%d %d", &binom1, &binom2);

    if (binom2 > binom1 - binom2)
        binom2 = binom1 - binom2;

    for (int i = 0; i < 40; i++)
    {
        if (i < binom2 + i)
        {
            num[i] = binom1;
            binom1--;

            denom[i] = binom2;
            binom2--;
        }
        else
        {
            num[i] = 1;
            denom[i] = 1;
        }
    }


        for (int i = 0; i < 40; i++)
        {
            for (int j = 0; j < 40; j++)
            {
                int lnko = gcd(num[i], denom[j]);
                num[i] = num[i] / lnko;
                denom[j] = denom[j] / lnko;
            }
        }

        for (int i = 0; i < 40; i++)
        {
            res = res * num[i];
        }


    printf("%llu", res);

    return 0;
}
