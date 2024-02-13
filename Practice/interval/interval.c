#include <stdio.h>

int interval(int startval, int len)
{
    int count = 0;
    for (int i = startval; i < startval + len; i++)
        if(i % 10 > ((i - i % 10) / 10) % 10)
            count++;
    return count;
}

int main(void)
{
    int a, b, minret, i = 0;
    while (scanf("%d %d", &a, &b) != EOF)
    {
        if (i == 0 || minret > interval(a, b))
            minret = interval(a, b);
        i++;
    }
    printf("%d", minret);
    return 0;
}