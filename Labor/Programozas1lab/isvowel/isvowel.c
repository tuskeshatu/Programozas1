#include <stdio.h>

int is_vowel(char letter)
{
    char vowel[] = {'a', 'e', 'i', 'o', 'u'};

    if (letter >= 'A' && letter < 'Z')
    {
        letter += 'a' - 'A';
    }
    

    for (int i = 0; i < 5; i++)
    {
        if (letter == vowel[i])
            return 1;
    }
    
    return 0;
}



int main(void)
{
    char letter;

    scanf("%c", &letter);

    printf("%d", is_vowel(letter));

    return 0;

}