#include <stdio.h>
#include <string.h>
	
enum { BUFFERSIZE = 128 };

void reverse_words(char str[])
{
    int i = 0, wordlen = 0;
    while (str[i] != '\0')
    {
        char buffer;
        if (str[i] == ' ')
        {
            str[i] = '\0';
            for (int k = (str + i) - wordlen * sizeof(char); str[k] != '\0'; k++)
            {
                buffer = str[k];
                str[k] = str[i - k];
                str[k + wordlen - (i )] = buffer;
            }
            
          //  strrev((str + i) - wordlen * sizeof(char));
            wordlen = 0;
        }

        i++;
        wordlen++;
    }

    for (int j = 0; j < i; j++)
    {
        if (str[j] == '\0')
            str[j] = ' ';
    }

    str[i] = '\0';
}


int main(void) {
	char buffer[BUFFERSIZE], *c;
	fgets(buffer, BUFFERSIZE, stdin);   // read from stdin until newline
	c = strchr(buffer, '\n');           // replace newline with '\0'
	if (c != NULL)
		*c = '\0';
	reverse_words(buffer);              // call user function
	printf("%s", buffer);               // print the modified string
	return 0;
}