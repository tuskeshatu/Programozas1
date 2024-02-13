#include <stdio.h>

int main(void)
{
    int bottom, top, hundreds, tens, ones;

    scanf("%d %d", &bottom, &top);
    for (int i = bottom; i < top; i++)
    {
        ones = i % 10;
        tens = i / 10 % 10;
        hundreds = i / 100 % 10;

        if (tens - ones == hundreds - tens)
            printf("%d ", i);
    }
    return 0;
}