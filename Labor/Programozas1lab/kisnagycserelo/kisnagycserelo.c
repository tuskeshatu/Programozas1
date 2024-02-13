#include <stdio.h>

int main(void)
{
    char charachter;

    while (scanf("%c", &charachter) == 1)
    {
        if (charachter >= 'A' && charachter <= 'Z')
            charachter = charachter - ('A' - 'a');
        else if(charachter >= 'a' && charachter <= 'z')
            charachter = charachter + ('A' - 'a');
        
        printf("%c", charachter);
    }
    

    return 0;
}