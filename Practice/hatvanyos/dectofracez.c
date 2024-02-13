#include <stdio.h>

int main()
{

    double n;
    int i, num, denom;

    scanf("%lf", &n);
    
     num = n*1e8;
     denom = 1e8;

     printf("%d/%d", num, denom);

    return 0;

}