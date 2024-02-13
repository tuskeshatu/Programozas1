#include <stdio.h>

int main()
{
    int number, k = 0;
    scanf("%d", &number);
    while (k * k < number)
    {
        k = k + 1;
    }
    if (k * k > number)
    {
        printf("Nem negyzetszam");
    }
    else
    {
        printf("Negyzetszam");
    }

    return 0;
}
