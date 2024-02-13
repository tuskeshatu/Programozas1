#include <stdio.h>

int main()
{
    int num, denom, curdenom = 1, i;

    scanf("%d %d", &num, &denom);

    while (1)
    {
        while (num*1.0/denom > 1.0/curdenom)
        {
            curdenom++;
        }
        
        
        
    }
    
    
    
    
    return 0;
}
