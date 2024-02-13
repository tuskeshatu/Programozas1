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
    int num[10], relprimecount = 0;

    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &num[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (relative_primes(num[i], num[j]))
            {
                relprimecount++;
            }
            
        }
        
    }
    
    
    printf("%d", relprimecount);

    return 0;
}