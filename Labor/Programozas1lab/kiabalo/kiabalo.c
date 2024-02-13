#include <stdio.h>

int main(void)
{
    char letter;
    int shout = 0, i = 0;

    while (scanf("%c", &letter) != EOF)
    {
        if (letter == ' ' || i == 0)
        {
            printf("%c", letter);
            shout = 0;

            if (letter >= 'A' && letter <= 'Z')
                shout = 1;

            if (scanf("%c", &letter) == EOF)
                break;

            if (letter >= 'A' && letter <= 'Z')
                shout = 1;
        }

        if (shout == 1 && letter >= 'a' && letter <= 'z')
            printf("%c", letter + ('A' - 'a'));
        else
            printf("%c", letter);

        i++;
    }

    return 0;
}
