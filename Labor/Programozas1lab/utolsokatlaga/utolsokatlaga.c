#include <stdio.h>

int main()
{

    double num[10] = {0}, sum = 0;
    int i = 0;

    while (1)
    {
        double temp;

        if (scanf("%lf", &temp) != 1)
            break;

        num[i % 10] = temp;

        i++;
    }

    for (int j = 0; j < 10; j++)
        sum = sum + num[j];

    if (i < 10)
        printf("%.3f", (double)sum / i);

    else
        printf("%.3f", (double)sum / 10.000);

    return 0;
}
