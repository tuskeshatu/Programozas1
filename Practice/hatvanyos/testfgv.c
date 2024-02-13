#include <stdio.h>

int hatvany (int a, int nv)
{
    int i = 1, ret = 1;

    while(i <= nv)
    {
        ret=ret*a;
        i++;
    }

    return ret;
}

int main()
{
    int a, nv, res;

    scanf("%d %d", &a, &nv);

    res = hatvany(a, nv);

    printf("%d", res);

    return 0;
}
