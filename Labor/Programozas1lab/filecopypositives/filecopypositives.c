#include <stdio.h>

int main()
{
    FILE *fsource = fopen("numbers.txt", "r");

    if (fsource == NULL)
        return 1;

    FILE *fdest = fopen("positive_numbers.txt", "w");
    
    double curnum;

    while (fscanf(fsource, "%lf", &curnum) != EOF)
        if(curnum > 0)
            fprintf(fdest, "%.4f ", curnum);
    

    return 0;
}
