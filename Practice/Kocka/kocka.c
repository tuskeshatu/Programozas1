#include <stdio.h>

int main()
{
    
    int a;
    int v;
    int f;

    scanf("%d", &a);

    v = a*a*a;
    f=6*(a*a);

    printf("A kocka oldalhossza %d m\nA kocka terfogata %d m3\nA kocka felszine %d m2", a, v, f);

    return 0;
}
