#include <stdio.h>

int main()
{
    
    int mark[5] = {0}, act;

    while (scanf("%d", &act) == 1)
    {
        mark[act-1]++;
    }
    
    for (int i = 4; i >= 0; i--)
    {
        printf("%d: %d db\n", i + 1, mark[i]);
    }
    

    return 0;
}
