#include <stdio.h>

int main()
{
    int a, b;
    long long int i = 1;
    double eps = 1e-6, sum = 0;

    printf("mettol meddig integraljam az x^2-et?: ");
    scanf("%d %d", &a, &b);

    for (i = 1; i * eps <= b - a; i++)
    {
        sum = sum + ((a + (i + 1) * eps) - (a + i * eps)) * ((a + (i + 1) * eps) * ((a + (i + 1) * eps)));

        if (i % 10000000000000 == 0)
        {
            printf("\n%f", sum);
        }
        
    }

    printf("\n------------------------\ni = %d\n\nx^2 integralja %d-tol %d-ig: %f\n", i, a, b, sum);
    

    return 0;
}