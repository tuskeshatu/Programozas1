#include <stdio.h>

int main(void)
{

    long long unsigned fibonacci[2];
    long long unsigned curfibonacci;
    int i = 0;

    scanf("%llu %llu", &fibonacci[0], &fibonacci[1]);

    while (1)
    {
        curfibonacci = fibonacci[0] + fibonacci[1];

        if (curfibonacci < fibonacci[1])
            break;

        fibonacci[0] = fibonacci[1];
        fibonacci[1] = curfibonacci;

        i++;
    }

    printf("%d", i + 1);

    return 0;
}