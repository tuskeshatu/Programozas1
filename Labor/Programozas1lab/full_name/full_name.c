#include <stdlib.h>

char *concatenate(char lastname[], char firstname[])
{
    int len, j = 0;
    for (len = 0; lastname[len] != '\0'; len++)
        ;
    for (int i; firstname[i] != '\0'; i++, len++)
        ;
    char *fullname = malloc(len + 2);
    for (int i = 0; lastname[i] != '\0'; i++, j++)
        fullname[j] = lastname[i];
    fullname[j] = ' ';
    j++;
    for (int i = 0; firstname[i] != '\0'; i++, j++)
        fullname[j] = firstname[i];
    fullname[j] = '\0';
    return fullname;
}

int main()
{
    char *pista = concatenate("Varga", "Ibolya");
}