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

int count_vowels(char str[])
{
    int vowel_count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (is_vowel(str[i]))
            vowel_count++;

    return vowel_count;
    
}

int main(void)
{
    char str[] = "Esik az eso!";
    int teszt = count_vowels(str);
}