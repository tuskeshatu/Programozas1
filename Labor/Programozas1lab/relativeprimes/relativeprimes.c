#include <stdio.h>

int gcd(int num1, int num2)
{
    int temp;

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

int relative_primes(int num1, int num2)
{
    if (gcd(num1, num2) == 1)
    {
        return 1;
    }

    return 0;
}

int main(void)
{
    int num1, num2, relprimecount = 0;

    while (scanf("%d %d", &num1, &num2) == 2)
    {
        relprimecount += relative_primes(num1, num2);
    }

    printf("%d", relprimecount);

    return 0;
}