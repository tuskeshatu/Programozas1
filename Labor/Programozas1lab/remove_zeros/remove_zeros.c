int remove_zeros(int arr[], int size_arr)
{
    int size_new_arr, j = 0;

    for (int i = 0; i < size_arr; i++, j++)
    {
        if (arr[i] == 0)
        {
            j--;
            continue;
        }
        arr[j] = arr[i];
    }

    return j;
}

int main(void)
{
    int arr[] = {0, 7};
    remove_zeros(arr, 2);

    //-2, -1, -3, 0, 3, 1, 0, -2, 3, 2, 0, 0, 0, -2, 3
}