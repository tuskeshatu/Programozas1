#include <stdio.h>
int surface(int a, int b, int c);

int main()
{
    int a, b, c;
    int sz;
    scanf("%d %d %d", &a, &b, &c);
    sz = surface(a, b, c);
    printf("felszin: %d \n", sz);
    printf()

        return 0;
}

int surface(int a, int b, int c)
{
    int s;
    s = 2 * (a * b + a * c + b * c);
    return s;
}