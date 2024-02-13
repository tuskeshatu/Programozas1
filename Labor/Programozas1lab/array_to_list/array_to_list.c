#include <stdlib.h>

typedef struct list_elem
{
    double data;
    struct list_elem *next;
} list_elem, *list_ptr;

list_ptr array_to_list(double arr[], int size_arr)
{
    if (arr == NULL || size_arr == 0)
        return  NULL;

    list_ptr curelem = NULL, head = NULL, prevelem = NULL;

    for (int i = size_arr; i > 0; i--)
    {
        curelem = malloc(sizeof(list_elem));
        if (curelem == NULL)
            return NULL;
        if (i == size_arr)
            head = curelem;
        else
            prevelem->next = curelem;
        curelem->data = arr[i - 1];
        prevelem = curelem;
    }
    curelem->next = NULL;

    return head;
}

int main()
{
    double doubles[3] = {0.1, 0.2, 0.3};

    list_ptr head = array_to_list(doubles, 3);
}