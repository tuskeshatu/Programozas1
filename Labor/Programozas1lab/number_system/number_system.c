#include <string.h>

unsigned str_to_num(char digits[], unsigned base)
{
    unsigned decimal = 0, curdigitval;
    
    for (int i = 0; digits[i] != '\0'; i++)
    {
        curdigitval = digits[i] - '0';

        decimal *= base;
        decimal += curdigitval;    
    }

    return decimal;
}

int main(void)
{
    unsigned faszomat = str_to_num("42", 10);
}