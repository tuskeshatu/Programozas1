#include <stdio.h>

int main()
{
    int cat, salary;

    scanf("%d %d", &cat, &salary);

    switch (cat)
    {
    case 0:
        printf("Bonus: 0 EUR");
        break;

    case 2:
        printf("Bonus: %d EUR", salary/10);
        break;

    case 1:
        printf("Bonus: 1000 EUR");
        break;

    case 3:
        printf("Bonus: %d EUR", salary/10+1000);
        break;

    default:
        printf("INVALID\nBonus: 0 EUR");
        break;
    }
    return 0;
}
