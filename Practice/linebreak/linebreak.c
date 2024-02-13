#include <stdio.h>

int main (void)
{
    int linepp, charpline, leftover, i = 0, totallen = 0;
    char text[1001];
    while (1)
    {
        scanf("%c", &text[i]);
        totallen++;
        if (text[i] == '#')
            break;
        i++;
    }
    scanf ("%d %d", &linepp, &charpline);

    int curwordlen = 0, curlinelen = 0, curpagelen = 0;
    i = 0;
    while (curpagelen < linepp)
    {
        while (text[i] != ' ' && text[i] != '#')
        {
            curwordlen++;
            i++;
        }
        
        if (curlinelen + curwordlen > charpline)
        {
            i -= curwordlen;
            curlinelen = 0;
            curpagelen++;
            curwordlen = 0;
            continue;
        }
        curlinelen += curwordlen + 1;
        curwordlen = 0;
        i++;
    }

    printf("%d", totallen - i - 1);

    return 0;
    
}