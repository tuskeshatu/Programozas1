void minmax(double arr[], int size_arr, double *p_min, double *p_max)
{
    *p_min = *p_max = arr[0];

    for (int i = 0; i < size_arr; i++)
    {
        if (arr[i] < *p_min)
            *p_min = arr[i];

        if (arr[i] > *p_max)
            *p_max = arr[i];
    }
}