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
    int hexval, decval;

    scanf("%c", &hexval);

    printf("%d", hexa_value(hexval));

    return 0;
}