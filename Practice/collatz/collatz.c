#include <stdio.h>

int main()
{
    int i = 0, ai;
    scanf("%d", &ai);
    while (ai != 1)
    {
        if (ai % 2 == 0)
        {
            ai = ai / 2;
        }
        else
        {
            ai = ai * 3 + 1;
        }
        i++;
    }
    printf("%d", i);
    return 0;
}
