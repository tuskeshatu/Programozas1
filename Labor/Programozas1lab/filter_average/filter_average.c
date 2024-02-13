#include <stdlib.h>

int *filter_average(int *original, int size_original, int *size_filtered)
{
    int sumoriginal = 0;
    double average;
    *size_filtered = 0;

    for (int i = 0; i < size_original; i++)
        sumoriginal += original[i];

    average = (double)sumoriginal / size_original;

    for (int i = 0; i < size_original; i++)
        if (original[i] < average)
            *size_filtered += 1;

    int *filtered = (int *)malloc(*size_filtered * sizeof(int));

    for (int i = 0, j = 0; i < size_original; i++)
        if (original[i] < average)
        {
            filtered[j] = original[i];
            j++;
        }
    return filtered;
}

int main()
{
    int tomb[] = {1, 2, 3};

    int sizefilter;
    int *filterelt = filter_average(tomb, 3, &sizefilter);
}