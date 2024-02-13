#include <stdio.h>
#include <string.h>
#define FILENAME_BUFFER 30
#define COPY_BUFFER 1024

int main()
{
    char fsourcename[FILENAME_BUFFER] = {0};
    scanf("%s", fsourcename);
    char fdestname[FILENAME_BUFFER] = {0};
    scanf("%s", fdestname);
    FILE *fsource = fopen(fsourcename, "r");
    FILE *fdest = fopen(fdestname, "w");

    if (fsource == NULL || fdest == NULL)
        return 1;

    char copy_buffer[1] = {0};
    while (fread(copy_buffer, 1, 1, fsource) > 0)
    {
        fwrite(copy_buffer, 1, 1, fdest);
    }

    fclose(fsource);
    fclose(fdest);

    return 0;
}