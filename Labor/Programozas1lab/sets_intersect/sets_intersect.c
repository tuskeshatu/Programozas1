#include <stdlib.h>

int isin(int arr[], int size_arr, int element)
{
    for (int i = 0; i < size_arr; i++)
        if (arr[i] == element)
            return 1;
    return 0;
}

int *intersection(int set1[], int size_set1, int set2[], int size_set2, int *size_intersect)
{
    *size_intersect = 0;

    for (int i = 0; i < size_set1; i++)
    {
        if (isin(set2, size_set2, set1[i]))
        {
            (*size_intersect)++;
        }
    }

    int *intersect = malloc(*size_intersect * sizeof(int));

    for (int i = 0, k = 0; i < size_set1; i++)
    {
        if (isin(set2, size_set2, set1[i]))
        {
            intersect[k] = set1[i];
            k++;
        }
    }

    return intersect;
}