#include <stdio.h>

int hexa_value(char hexval)
{
    if (hexval >= 'A' && hexval <= 'F')
    {
        hexval += 'a' - 'A';
    }

    if (hexval >= '0' && hexval <= '9')
        return hexval - '0';

    if (hexval >= 'a' && hexval <= 'f')
        return hexval - 'a' + 10;

    return -1;
}

int main(void)
{
    int hexcurval, decval = 0;

    while (scanf("%c", &hexcurval) == 1)
    {
        if (hexa_value(hexcurval) == -1)
            continue;
        
        decval *= 16;
        decval += hexa_value(hexcurval);
        
    }

    printf("%d", decval);

    return 0;
}