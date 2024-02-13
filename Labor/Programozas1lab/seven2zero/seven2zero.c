void seven_to_zero(int arr[], int size_arr)
{
    for (int i = 0; i < size_arr; i++)
    {
        if (arr[i] % 7 == 0)
            arr[i] = 0;
    }
    
}