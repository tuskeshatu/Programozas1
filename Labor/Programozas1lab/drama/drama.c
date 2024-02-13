#include <stdio.h>
#include <string.h>
#define MAX_FILENAME 30
#define MAX_NAME_LEN 20
#define MAX_LINE_LEN 100

char *lower2upper(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] += ('A' - 'a');
        i++;
    }
}

int main()
{
    char sourcefilename[MAX_FILENAME] = {0}, name[MAX_NAME_LEN] = {0}, buffer[MAX_LINE_LEN], destfilename[MAX_FILENAME];

    scanf("%s %s", sourcefilename, name);

    strcpy(destfilename, name);
    strcat(destfilename, ".txt");

    FILE *fdest = fopen(destfilename, "w");
    if (fdest == NULL)
        return 1;

    lower2upper(name);

    FILE *fsource = fopen(sourcefilename, "r");

    if (fsource == NULL)
        return 1;

    while (fgets(buffer, MAX_LINE_LEN, fsource) != NULL)
    {
        if (strstr(buffer, name))
        {

            while (buffer[0] != '\n')
            {
                char temp[MAX_LINE_LEN];
                fgets(buffer, MAX_LINE_LEN, fsource);
                strcpy(temp, &buffer[1]);
                fprintf(fdest, "%s", temp);
            }
            fprintf(fdest, "\n");
        }
    }

    fclose(fdest);
    fclose(fsource);

    return 0;
}
