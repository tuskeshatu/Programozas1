#include <stdlib.h>

typedef struct _listelem
{
    double data;
    struct _listelem *next;
} listelem;

listelem *list_from_array(double t[], int n)
{
    listelem *last = NULL;
    int i;
    for (i = n - 1; i >= 0; i--)
    {
        listelem *new = (listelem *)malloc(sizeof(listelem));
        new->data = t[i];
        new->next = last;
        last = new;
    }
    return last;
}

void free_list(listelem *root)
{
    while (root != NULL)
    {
        listelem *next = root->next;
        free(root);
        root = next;
    }
}

listelem *merge(listelem *a, listelem *b)
{
    listelem *head, *temp, *lastelem;

    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    if (a->data < b->data)
    {
        head = a;
        lastelem = a;
        a = a->next;
    }
    else
    {
        head = b;
        lastelem = b;
        b = b->next;
    }

    while (a != NULL && b != NULL)
    {
        if (a->data < b->data)
        {
            lastelem->next = a;
            lastelem = a;
            a = a->next;
        }
        else
        {
            lastelem->next = b;
            lastelem = b;
            b = b->next;
        }
    }

    if (a != NULL)
        lastelem->next = a;
    if (b != NULL)
        lastelem->next = b;
    

    return head;
}

int main()
{
    double arr1[] = {3.5, 11.4, 13.4, 24.7};
    double arr2[] = {2.9, 13.9, 17.6, 17.8};

    listelem *list1 = list_from_array(arr1, 4);
    listelem *list2 = list_from_array(arr2, 3);

    listelem *merged = merge(list1, list2);
}