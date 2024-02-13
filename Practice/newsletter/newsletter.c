#include <stdio.h>

void mail_merge(char origin[], char name[], char res[])
{
    int i = 0, k = 0;
    while (origin[i] != '\0')
    {
        if (origin[i] == '#')
        {
            int j = 0;
            while (name [j] != '\0')
            {
                res[k] = name[j];
                k++;
                j++;
            }
            i++;
            continue;
        }
        res[k] = origin[i];
        i++;
        k++;
    }
    res[k] = '\0';
}

int main (void)
{
    char original[] = "Oh #, miert vagy te #?", name[] = "Julia",  result[31];

    mail_merge(original, name, result);

    for (int i = 0; i < 31; i++)
        printf("%c", result[i]);
    
    return 0;

}