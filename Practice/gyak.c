#include <stdio.h>
#include <stdlib.h>

void p(int s)
{
    printf("%d ", s);
}

void suicide(size_t fasz)
{
    while (1)
    {
        malloc(fasz);
    }
    
}

void q(int s)
{
    for (size_t i = 0; i < s; i++)
    {
        putc('*', stdout);
    }
    putc('\n', stdout);
}

void kiir(int t[], int n, void (*ki)(int))
{
    for (size_t i = 0; i < n; i++)
    {
        ki(t[i]);
    }
}

int main(int argc, char const *argv[])
{
    int t[] = {6,4,8,3,6,4,2,45,7};

    kiir(t, 9, q);
}