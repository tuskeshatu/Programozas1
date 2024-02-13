#include <string.h>
void copy_nth_words(char origin[], char res[], int nth)
{
    int wordcnt = 0, wordlen = 0, i = 0, j = 0;

    while (origin[i] != '\0' || strlen(origin) + 1 == i)
    {
        if (origin[i] == ' ')
        {
            wordcnt++;
            if ((wordcnt - 1) % nth == 0)
            {
                if (wordcnt != 1)
                {
                    origin[i] = '\0';
                }
                strcpy(&res[j], &origin[i - wordlen]);
                j += wordlen;
            }
            wordlen = 0;
        }
        i++;
        wordlen++;
    }
}

int main(void)
{
    char str1[] = "cica hollo varju kutya mokus beka csiga";
    char ressrt[100] = {0};
    int n = 3;
    copy_nth_words(str1, ressrt, n);
}