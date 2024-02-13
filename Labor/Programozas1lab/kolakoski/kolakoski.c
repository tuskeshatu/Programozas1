#include <stdio.h>

int main()
{
    int seq[100] = {1, 2}, val, curnum = 1, blocksize = 1, curblockidx = 1;

    scanf("%d", &val);

    for (int i = 0; i < 100; i++)
    {
        seq[i] = curnum;
        printf("%d ", curnum);
        blocksize--;

        if (blocksize == 0)
        {
            blocksize = seq[curblockidx];
            curnum++;
            curblockidx++;
        }
        
        if (curnum > val)
            curnum = 1;
    }
    
    
    return 0;
}
