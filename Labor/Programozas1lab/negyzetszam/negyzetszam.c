#include <stdio.h>

int main()
{

    int n, i = 0;

    scanf("%d", &n);

    while (i*i < n)
    {
        i++;
        
    }


    if (i*i == n)
    {
        printf("Negyzetszam");

    }
    else
    {

        printf("Nem negyzetszam");
    
    }
    
    


    return 0;
}
